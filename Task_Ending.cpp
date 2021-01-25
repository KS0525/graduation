//-------------------------------------------------------------------
//GfBO
//-------------------------------------------------------------------
#include  "MyPG.h"
#include  "Task_Ending.h"
#include  "Task_Title.h"

#include "easing.h"
namespace  Ending
{
	Resource::WP  Resource::instance;
	//-------------------------------------------------------------------
	//\[XΜϊ»
	bool  Resource::Initialize()
	{
		this->img = DG::Image::Create("./data/image/Ending.bmp");
		//this->back = DG::Image::Create("./data/image/UI/back1.png");
		//this->back2 = DG::Image::Create("./data/image/UI/back2.png");
		//this->back3 = DG::Image::Create("./data/image/UI/back3.png");
		//this->back4 = DG::Image::Create("./data/image/UI/back4.png");


		this->back = DG::Image::Create("./data/image/UI/select3-2.png");
		this->back2 = DG::Image::Create("./data/image/UI/select3-3.png");
		this->back3 = DG::Image::Create("./data/image/UI/select3-4.png");
		this->back4 = DG::Image::Create("./data/image/UI/select3-5.png");

		return true;
	}
	//-------------------------------------------------------------------
	//\[XΜπϊ
	bool  Resource::Finalize()
	{
		this->img.reset();
		return true;
	}
	//-------------------------------------------------------------------
	//uϊ»v^XNΆ¬ΙPρΎ―s€
	bool  Object::Initialize()
	{
		//X[p[NXϊ»
		__super::Initialize(defGroupName, defName, true);
		//\[XNXΆ¬or\[X€L
		this->res = Resource::Create();

		//f[^ϊ»

		//^XNΜΆ¬

		return  true;
	}
	//-------------------------------------------------------------------
	//uIΉv^XNΑΕΙPρΎ―s€
	bool  Object::Finalize()
	{
		//f[^^XNπϊ
		ge->KillAll_G("wiζ");

		if (!ge->QuitFlag() && this->nextTaskCreate) {
			//ψ«p¬^XNΜΆ¬
			auto  nextTask = Title::Object::Create(true);
		}

		return  true;
	}
	//-------------------------------------------------------------------
	//uXVvPt[Ιs€
	void  Object::UpDate()
	{
		auto ms = ge->mouse->GetState();
		auto key = ge->in1->GetState();

		if (key.B1.down) {
			this->Kill();
		}

		if (ms.RB.down) {

		}
		if (ms.LB.down) {
			//©gΙΑΕvΏ
			this->Kill();
		}
	}
	//-------------------------------------------------------------------
	//uQc`ζvPt[Ιs€
	void  Object::Render2D_AF()
	{
		ML::Box2D  draw(0, 0, ge->screenWidth, ge->screenHeight);
		ML::Box2D  src(0, 0, 240, 135);

		draw.Offset(0, this->logoPosY);
		this->res->img->Draw(draw, src);

	/*	for (int i = 0; i < 4; ++i) {
			ML::Box2D draw2(i * 200, 640, 128, 128);
			ML::Box2D src2(0, 0, 128, 128);
			this->res->back->Draw(draw2, src2);
		}*/
		ML::Box2D draw1(200, 600, 170, 128);
		ML::Box2D draw2(400, 600, 170, 128);
		ML::Box2D draw3(600, 600, 170, 128);
		ML::Box2D draw4(800, 600, 170, 128);
		ML::Box2D src2(0, 0, 170, 128);

		this->res->back->Draw(draw1, src2);
		this->res->back2->Draw(draw2, src2);
		this->res->back3->Draw(draw3, src2);
		this->res->back4->Draw(draw4, src2);

	}

	//
	//ΘΊΝξ{IΙΟXsvΘ\bh
	//
	//-------------------------------------------------------------------
	//^XNΆ¬ϋ
	Object::SP  Object::Create(bool  flagGameEnginePushBack_)
	{
		Object::SP  ob = Object::SP(new  Object());
		if (ob) {
			ob->me = ob;
			if (flagGameEnginePushBack_) {
				ge->PushBack_ABCDEFGHIJKLMN(ob);//Q[GWΙo^
			}
			if (!ob->B_Initialize()) {
				ob->Kill();//CjVCYΙΈs΅½ηKill
			}
			return  ob;
		}
		return nullptr;
	}
	//-------------------------------------------------------------------
	bool  Object::B_Initialize()
	{
		return  this->Initialize();
	}
	//-------------------------------------------------------------------
	Object::~Object() { this->B_Finalize(); }
	bool  Object::B_Finalize()
	{
		auto  rtv = this->Finalize();
		return  rtv;
	}
	//-------------------------------------------------------------------
	Object::Object() {	}
	//-------------------------------------------------------------------
	//\[XNXΜΆ¬
	Resource::SP  Resource::Create()
	{
		if (auto sp = instance.lock()) {
			return sp;
		}
		else {
			sp = Resource::SP(new  Resource());
			if (sp) {
				sp->Initialize();
				instance = sp;
			}
			return sp;
		}
	}
	//-------------------------------------------------------------------
	Resource::Resource() {}
	//-------------------------------------------------------------------
	Resource::~Resource() { this->Finalize(); }
}