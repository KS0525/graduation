//-------------------------------------------------------------------
//^Cgๆส
//-------------------------------------------------------------------
#include  "MyPG.h"
#include  "Task_MapSelector.h"
#include  "Task_BackGround.h"
#include  "Task_Game.h"

#include "easing.h"

namespace  MapSelector
{
	Resource::WP  Resource::instance;
	//-------------------------------------------------------------------
	//\[Xฬ๚ป
	bool  Resource::Initialize()
	{
		this->img = DG::Image::Create("./data/image/Block/Block_00.jpg");
		this->choosingimg = DG::Image::Create("./data/image/UI/UI_choosing.png");
		return true;
	}
	//-------------------------------------------------------------------
	//\[Xฬ๐๚
	bool  Resource::Finalize()
	{
		
		return true;
	}
	//-------------------------------------------------------------------
	//u๚ปv^XNถฌษP๑พฏsค
	bool  Object::Initialize()
	{
		//X[p[NX๚ป
		__super::Initialize(defGroupName, defName, true);
		//\[XNXถฌor\[XคL
		this->res = Resource::Create();

		this->render2D_Priority[1] = 0.5f;

		//Button::set_allNum(0);
		buttons[0].set_StagePass("./data/Map/Map.txt");
		buttons[1].set_StagePass("./data/Map/Map4.txt");
		buttons[2].set_StagePass("./data/Map/Map3.txt");
		buttons[3].set_StagePass("./data/Map/Map5.txt");
		buttons[4].set_StagePass("./data/Map/Map6.txt");
		buttons[5].set_StagePass("./data/Map/Map7.txt");
		buttons[6].set_StagePass("./data/Map/Map8.txt");
		buttons[7].set_StagePass("./data/Map/Map9.txt");
		buttons[8].set_StagePass("./data/Map/Map10.txt");
		buttons[9].set_StagePass("./data/Map/Map11.txt");
		buttons[10].set_StagePass("./data/Map/Map12.txt");
		buttons[11].set_StagePass("./data/Map/Map13.txt");
		buttons[12].set_StagePass("./data/Map/Map14.txt");
		buttons[13].set_StagePass("./data/Map/Map15.txt");


		//f[^๚ป
		//easing::Init();
		BackGround::Object::Create(true);
		choosing = 1;
		choiceMax_ = sizeof(buttons)/sizeof(buttons[0]);
		//^XNฬถฌ
		
		return  true;
	}
	//-------------------------------------------------------------------
	//uIนv^XNมลษP๑พฏsค
	bool  Object::Finalize()
	{
		//f[^^XN๐๚
		ge->KillAll_G("wiๆ");

		if (!ge->QuitFlag() && this->nextTaskCreate) {
			//๘ซpฌ^XNฬถฌ
			auto nextTask = Game::Object::Create(true);
		}
		return  true;
	}
	//-------------------------------------------------------------------
	//uXVvPt[ษsค
	void  Object::UpDate()
	{
		auto ms = ge->mouse->GetState();
		auto key = ge->in1->GetState();
		Carsol();
		
		if (key.B1.down) {
			ge->nowStage = buttons[choosing].get_StagePass();
				//ฉgษมลvฟ
				this->Kill();
			}
		//}

	}
	//-------------------------------------------------------------------
	//uQc`ๆvPt[ษsค
	void  Object::Render2D_AF()
	{
#define choiceMax 14
		ML::Box2D draw[choiceMax] = {
			ML::Box2D(100,100,100,100),
			ML::Box2D(200,100,100,100),
			ML::Box2D(300,100,100,100),
			ML::Box2D(400,100,100,100),
			ML::Box2D(500,100,100,100),
			ML::Box2D(600,100,100,100),
			ML::Box2D(700,100,100,100),
			ML::Box2D(800,100,100,100),
			ML::Box2D(100,300,100,100),
			ML::Box2D(200,300,100,100),
			ML::Box2D(300,300,100,100),
			ML::Box2D(400,300,100,100),
			ML::Box2D(500,300,100,100),
			ML::Box2D(600,300,100,100),
		};
		ML::Box2D  draw1(100,100, 100, 100);
		ML::Box2D  src1(0, 0, 128, 128);
		this->res->img->Draw(draw1, src1);
		
		for (int i = 1; i < choiceMax; ++i) {
			this->res->img->Draw(draw[i], src1);
		}
		/*this->res->img->Draw(draw[1], src1);
		this->res->img->Draw(draw[2], src1);
		this->res->img->Draw(draw[3], src1);
		this->res->img->Draw(draw[4], src1);*/

		ML::Box2D src2(0, 0, 132, 132);
		this->res->choosingimg->Draw(draw[choosing], src2);
		
	}
	//------------------------------------------------------------------
	void Object::Carsol() 
	{
		auto key = ge->in1->GetState();
		//J[\ฺฎ
		if (key.LStick.BR.down) {
			choosing++;
		}
		if (key.LStick.BL.down) {
			choosing--;
		}
		//บภฦใภ
		if (choosing < 0) {
			choosing = 0;
		}
		if (choosing > this->choiceMax_) {
			choosing = choiceMax_;
		}
	}
	//
	//ศบอ๎{IษฯXsvศ\bh
	//
	//-------------------------------------------------------------------
	//^XNถฌ๛
	Object::SP  Object::Create(bool  flagGameEnginePushBack_)
	{
		Object::SP  ob = Object::SP(new  Object());
		if (ob) {
			ob->me = ob;
			if (flagGameEnginePushBack_) {
				ge->PushBack_ABCDEFGHIJKLMN(ob);//Q[GWษo^
			}
			if (!ob->B_Initialize()) {
				ob->Kill();//CjVCYษธsตฝ็Kill
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
	//\[XNXฬถฌ
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