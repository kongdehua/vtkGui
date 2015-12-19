# vtkGui

Create README.md

## 简介
为了生成OpenGL下的魔兽世界中的对话框，完成这个功能需要使用以下两个组件：vtk和fltk。 其中：
1. vtk是跨平台的三维显示工具，使用标准OpenGL作为基本显示组件，以C++语言编写，实现了跨平台。
2. fltk是跨平台的GUI工具包，通过为不同系统分别实现显示方式，通过宏控制各个系统的编译，以C++语言编写，实现了跨平台。

本工程的目标是在vtk上实现2D界面窗口，使用fltk的界面绘制方式，事件的处理也模拟fltk，希望能够实现出vtk上的二维窗口。

## 分期
为了实现这个目标，将工程分为三期：
1. 仅仅实现Window和Button，能够在vtk上面显示Window和Button，并且能够拖动窗口，以及响应鼠标按键。

2. 实现除Button外的简单2D控件，包括文本框、单选按钮、多选按钮等，能够在vtk上面显示它们，并且能够操作，以及响应鼠标键盘事件。

3. 实现树控件吧。。。。。也不知道什么时候，就算有fltk作为参考。。。。。

## 一期计划
即使将目标定的这么低，似乎还是有些难度啊。。。。

### 理解vtk的2D实现方式
首先，vtk支持2D显示的方式大概有两种：

1. 以vtkActor2D为主，使用方式和vtkActor基本相同，区别仅仅是渲染函数不相同；使用步骤如下：
* 使用vtkRenderWindow构建窗口,
* 添加一个vtkRenderer到窗口中，
* 以vtkRenderWindowInteractor作为交互器，
* 构建vtkInteractorStyle设置到交互器中（这也是一个重要的区别，2D、3D毕竟不一样，交互方式也会存在区别就可以理解了），
* 添加vtkActor2D到vtkRenderer中；

2. 第二种方式看起来似乎简单得多，实际还是稍微复杂一些，看起来以vtkContextView为主，在里面添加vtkAbstractContextItem的子类看起来就可以了。

这种实现方式与第一种的难度其实差不多，纵观vtkContextView其实提供了一个vtkContextScene的显示结构，主要的功能由vtkContextScene提供。

vtkContextView 继承自 vtkRenderViewBase，额外包含两个变量：vtkContextScene和vtkContext2D。

在vtkRenderViewBase的构造函数中，可喜地看到一个构建vtkRenderWindow的常见过程，当然没有出现vtkInteractorStyle，对应地，在vtkContextView中当然就出现了vtkContextInteractorStyle。这里有几个值得注意的地方:
* 首先，vtkContext2D需要绑定vtkOpenGLContextDevice2D，经过实验，初步鉴定，似乎没它也没关系；
* vtkContextActor、vtkContextScene之间的关系错综复杂，
vtkContextActor添加到Renderer中后，取出vtkContextScene，并且需要在Scene上绑定vtkRenderer。这个其实没那么复杂，实现者将他复杂化了，必要的操作：添加Actor、设置Scene、设置Renderer就可以了。

	vtkContextActor *actor = vtkContextActor::New();
	this->Renderer->AddActor(actor);
	actor->Delete();

	this->Scene = actor->GetScene();
	this->Scene->SetRenderer(this->Renderer);

这个部分几乎就无障碍了。

### vtk的2D结构
首先，建立可支持2D的vtk程序结构：
目标是在同一场景中同时进行2D和3D的操作，似乎可行的方法还是利用Interactor中的优先级Priority来控制场景的操作。具体来说就是：2D部分的操作优先级高，如果获取了权限，立刻GrabFocus()来确保操作完成。当然，如果被3D部分获得了权限，也需要用GrabFocus()来确保操作完成。

实现方式，大概使用Interaction中的大量已存在vtkWidget的方式。

### vtk的实现方案
1. 创建一个工程，主函数中使用vtkContextView，使用vtkAbstractContextItem绘制图形；（Charts中提供了不少的案例）
主要需要实现两种功能的函数：绘制、事件处理;

绘制函数：必然使用基础功能中的绘制函数，例如：fltk分别使用不同系统的独自的画线函数，所以，准备使用vtk中自带的绘制函数。

在vtkAbstractContextItem的绘制函数定义：
	
	bool vtkAbstractContextItem::Paint(vtkContext2D *painter);

vtk中可使用的绘制函数基本都包含在vtkContext2D中。vtkContext2D中提供绘制2D基元。

	DrawLine // Draw a line
	DrawPoly // Draw a poly line between the specified points
	DrawPoint
	DrawMarker
	DrawRect
	DrawQuad
	DrawPolygon
	DrawImage
	DrawStringRect // in Rect
	DrawString

基本提供了以上功能函数，对于这些功能函数，基本可以直接使用。


### vtk的fltk实现方案

