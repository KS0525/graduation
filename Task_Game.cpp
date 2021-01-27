//-------------------------------------------------------------------
//Q[{า
//-------------------------------------------------------------------
#include  "MyPG.h"
#include  "Task_Game.h"
#include  "Task_Ending.h"
#include  "Task_Player.h"
#include  "Task_BackGround.h"
#include  "Task_Enemy.h"
#include  "Task_Block00.h"
#include  "Task_EffectBomb.h"
#include  "Task_EffectHit.h"
#include  "Task_Enemy01.h"
#include  "Task_Map2D.h"
#include  "Task_Block01.h"
#include  "Task_MapGenerator.h"
#include  "Task_MapSelector.h"
#include  "Task_StageSelector.h"
#include  "Task_Block02.h"

namespace  Game
{
	Resource::WP  Resource::instance;
	//-------------------------------------------------------------------
	//\[Xฬ๚ป
	bool  Resource::Initialize()
	{
		this->grab_UI_img = DG::Image::Create("./data/image/UI/gravity_UI-6.png");
		this->grab_UI_img2 = DG::Image::Create("./data/image/UI/gravity_UI-5.png");

		this->grab_up_01 = DG::Image::Create("./data/image/UI/gravity_UI-6.png");
		this->grab_up_02 = DG::Image::Create("./data/image/UI/gravity_UI-5.png");

		this->grab_left_01 = DG::Image::Create("./data/image/UI/gravity_left01.png");
		this->grab_left_02 = DG::Image::Create("./data/image/UI/gravity_left02.png");

		this->grab_right_01 = DG::Image::Create("./data/image/UI/gravity_right01.png");
		this->grab_right_02 = DG::Image::Create("./data/image/UI/gravity_right02.png");

		this->grab_under_01 = DG::Image::Create("./data/image/UI/gravity_under01.png");
		this->grab_under_02 = DG::Image::Create("./data/image/UI/gravity_under02.png");

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

		//f[^๚ป
		this->count = 0;
		this->bcount = 0;
		
		ge->camera2D = ML::Box2D(0,0, ge->screen2DWidth, ge->screen2DHeight);

		//XRA๚ป
		ge->score = 0;
		ge->gameClearFlag = false;
	   //^XNฬถฌ
		BackGround::Object::Create(true);

		if (auto map = Generator::Object::Create_Mutex()) {
			map->Set(ge->nowStage);
		}

		return  true;
	}
	//-------------------------------------------------------------------
	//uIนv^XNมลษP๑พฏsค
	bool  Object::Finalize()
	{
		//f[^^XN๐๚
		ge->KillAll_G("vC[");
		ge->KillAll_G("wiๆ");
		ge->KillAll_G("G");
		ge->KillAll_G("e");
		ge->KillAll_G("ubN");
		ge->KillAll_G("XCb`");
		ge->KillAll_G("S[");

		if (!ge->QuitFlag() && this->nextTaskCreate) {
			//๘ซpฌ^XNฬถฌ
			if (ge->gameClearFlag) {
				auto nextTask = Ending::Object::Create(true);
			}
			else {
				auto nextTask = MapSelector::Object::Create(true);
			}
		}

		return  true;
	}
	//-------------------------------------------------------------------
	//uXVvPt[ษsค
	void  Object::UpDate()
	{
		auto ms = ge->mouse->GetState();
		auto key = ge->in1->GetState();

		if (key.LStick.BU.on) { this->MoveGravity = Gravity::up; }
		if (key.LStick.BL.on) { this->MoveGravity = Gravity::left; }
		if (key.LStick.BD.on) { this->MoveGravity = Gravity::down; }
		if (key.LStick.BR.on) { this->MoveGravity = Gravity::right; }
		
		if (ge->isReady) {
			if (ms.RB.down || key.B2.down) {
				ge->KillAll_G("vC[");
				ge->KillAll_G("ubN");
				ge->KillAll_G("ล่ubN");
				ge->KillAll_G("XCb`");
				ge->KillAll_G("S[");

				if (auto map = Generator::Object::Create_Mutex()) {
					map->Set(ge->nowStage);
				}
				ge->isReady = false;
			}
		}

		if (ms.CB.down ) {
			//ฉgษมลvฟ
			this->Kill();
		}
	}
	//-------------------------------------------------------------------
	//uQc`ๆvPt[ษsค
	void  Object::Render2D_AF()
	{
		auto key = ge->in1->GetState();
		ML::Box2D draw(80,80,96,96);
		ML::Box2D src(0, 0, 136, 136);
	
		float pie(3.1415f);

		switch (this->MoveGravity) {
		case 0: //up
			//this->res->grab_UI_img->Rotation(0*pie, ML::Vec2((draw.x + draw.w) / 2, (draw.y + draw.h) / 2));
			//this->res->grab_UI_img2->Rotation(0*pie, ML::Vec2((draw.x + draw.w) / 2, (draw.y + draw.h) / 2));
			this->res->grab_UI_img = this->res->grab_up_01;
			this->res->grab_UI_img2 = this->res->grab_up_02;
			break;
		case 1: // down
			//this->res->grab_UI_img->Rotation(pie, ML::Vec2((draw.x + draw.w) / 2, (draw.y + draw.h) / 2));
			//this->res->grab_UI_img2->Rotation(pie, ML::Vec2((draw.x + draw.w) / 2, (draw.y + draw.h) / 2));
			this->res->grab_UI_img = this->res->grab_under_01;
			this->res->grab_UI_img2 = this->res->grab_under_02;
			break;
		case 2: //left
			//this->res->grab_UI_img->Rotation(1.5f * pie, ML::Vec2((draw.x + draw.w) / 2, (draw.y + draw.h) / 2));
			//this->res->grab_UI_img2->Rotation(1.5f * pie, ML::Vec2((draw.x + draw.w) / 2, (draw.y + draw.h) / 2));
			this->res->grab_UI_img = this->res->grab_left_01;
			this->res->grab_UI_img2 = this->res->grab_left_02;
			break;
		case 3: //right
			//this->res->grab_UI_img->Rotation(0.5f * pie, ML::Vec2((draw.x + draw.w) / 2, (draw.y + draw.h) / 2));
			//this->res->grab_UI_img2->Rotation(0.5f * pie, ML::Vec2((draw.x + draw.w) / 2, (draw.y + draw.h) / 2));
			this->res->grab_UI_img = this->res->grab_right_01;
			this->res->grab_UI_img2 = this->res->grab_right_02;
			break;
		default:

			break;
		}

		if (key.LStick.volume != 0) {
			this->res->grab_UI_img2->Draw(draw, src);
		}
		else {
			this->res->grab_UI_img->Draw(draw, src);
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