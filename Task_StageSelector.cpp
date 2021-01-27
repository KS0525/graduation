//-------------------------------------------------------------------
//^Cgๆส
//-------------------------------------------------------------------
#include  "MyPG.h"
#include  "Task_StageSelector.h"
#include  "Task_BackGround.h"
#include  "Task_Game.h"
#include  "Task_MapSelector.h"

#include "easing.h"

namespace  StageSelector
{
	Resource::WP  Resource::instance;
	//-------------------------------------------------------------------
	//\[Xฬ๚ป
	bool  Resource::Initialize()
	{
		this->eggCapsule = DG::Image::Create("./data/image/Select/Select_body.png");

		this->nonClearEgg[0] = DG::Image::Create("./data/image/Select/Select_toumeiEgg_01_.png");
		this->nonClearEgg[1] = DG::Image::Create("./data/image/Select/Select_toumeiEgg_02_.png");
		this->nonClearEgg[2] = DG::Image::Create("./data/image/Select/Select_toumeiEgg_03_.png");
		this->nonClearEgg[3] = DG::Image::Create("./data/image/Select/Select_toumeiEgg_04_.png");
		this->nonClearEgg[4] = DG::Image::Create("./data/image/Select/Select_toumeiEgg_05_.png");
		this->nonClearEgg[5] = DG::Image::Create("./data/image/Select/Select_toumeiEgg_06_.png");

		this->clearEgg[0] = DG::Image::Create("./data/image/Select/Select_Egg_01.png");
		this->clearEgg[1] = DG::Image::Create("./data/image/Select/Select_Egg_02.png");
		this->clearEgg[2] = DG::Image::Create("./data/image/Select/Select_Egg_03.png");
		this->clearEgg[3] = DG::Image::Create("./data/image/Select/Select_Egg_04.png");
		this->clearEgg[4] = DG::Image::Create("./data/image/Select/Select_Egg_05.png");
		this->clearEgg[5] = DG::Image::Create("./data/image/Select/Select_Egg_06.png");

		this->selectEgg[0] = DG::Image::Create("./data/image/Select/Select_select_01.png");
		this->selectEgg[1] = DG::Image::Create("./data/image/Select/Select_select_02.png");
		this->selectEgg[2] = DG::Image::Create("./data/image/Select/Select_select_03.png");
		this->selectEgg[3] = DG::Image::Create("./data/image/Select/Select_select_04.png");
		this->selectEgg[4] = DG::Image::Create("./data/image/Select/Select_select_05.png");
		this->selectEgg[5] = DG::Image::Create("./data/image/Select/Select_select_06.png");

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

		/*buttons[0].set_StagePass("./data/Map/}bv/Map20.txt");
		buttons[1].set_StagePass("./data/Map/}bv/Map21.txt");
		buttons[2].set_StagePass("./data/Map/}bv/Map22.txt");
		buttons[3].set_StagePass("./data/Map/}bv/Map141.txt");
		buttons[4].set_StagePass("./data/Map/}bv/Map151.txt");
		buttons[5].set_StagePass("./data/Map/}bv/Map161.txt");*/
		

		string pass = "./data/Map/" + to_string(mapNumber) + "/Map1.txt";

		buttons[0].set_StagePass(pass);
		buttons[1].set_StagePass("./data/Map/" + to_string(mapNumber) + "/Map2.txt");
		buttons[2].set_StagePass("./data/Map/" + to_string(mapNumber) + "/Map3.txt");
		buttons[3].set_StagePass("./data/Map/" + to_string(mapNumber) + "/Map4.txt");
		buttons[4].set_StagePass("./data/Map/" + to_string(mapNumber) + "/Map5.txt");
		buttons[5].set_StagePass("./data/Map/" + to_string(mapNumber) + "/Map6.txt");

		//buttons[0].set_StagePass("./data/Map/1/Map6.txt");

		//f[^๚ป
		//easing::Init();
		BackGround::Object::Create(true);
		choosing = 0;
		animCnt = 0;
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
		
		animCnt++;
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
		ML::Box2D  draw1(0,0, 1280, 720);
		ML::Box2D  src1(0, 0, 1280, 720);
		this->res->eggCapsule->Draw(draw1, src1);
		
		for(int i = 0;i<6;++i){
			this->res->nonClearEgg[i]->Draw(draw1, src1);
		}
		if (animCnt %60 > 0 && animCnt %60 < 30) {
			this->res->selectEgg[choosing]->Draw(draw1, src1);
		}
		else {

		}
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
			choosing = this->choiceMax_ -1;
		}
		if (choosing >= this->choiceMax_) {
			choosing = 0;
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