//-------------------------------------------------------------------
//
//-------------------------------------------------------------------
#include  "MyPG.h"
#include  "Task_EffectCreate.h"

#include "Task_EffectBomb.h"
#include "Task_EffectHit.h"

namespace  EffectCreate
{
	Resource::WP  Resource::instance;

	void Object::CreateEffect(Object::EFFECTTYPE type, ML::Vec2 p, float scale_)
	{
		switch (type)
		{

		case EFFECTTYPE::HIT:
		{
			auto  h = EffectHit::Object::Create(true);
			h->pos = p;
			h->sizeH = 50;
			h->sizeW = 50;
			h->scale = scale_;
		}
		break;
		case EFFECTTYPE::L_MYST:

			break;
		case EFFECTTYPE::R_MYST:

			break;
		case EFFECTTYPE::N_MYST:

			break;
		case EFFECTTYPE::BOMB:
		{
			auto  b = EffectBomb::Object::Create(true);
			b->pos = p;
			b->sizeH = 400;
			b->sizeW = 400;
			b->scale = scale_;
		}
		break;
		case EFFECTTYPE::BOMBRING:

			break;

		case EFFECTTYPE::BOMBCHORD:


			break;

		case EFFECTTYPE::BOMBMINI:
		{
			auto b = EffectBomb::Object::Create(true);
			b->pos = p;
			b->sizeH = 40;
			b->sizeW = 40;
			b->scale = scale_;
		}
		break;
			
		}
	

	}

	//-------------------------------------------------------------------
	//\[XΜϊ»
	bool  Resource::Initialize()
	{
		return true;
	}
	//-------------------------------------------------------------------
	//\[XΜπϊ
	bool  Resource::Finalize()
	{
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


		if (!ge->QuitFlag() && this->nextTaskCreate) {
			//ψ«p¬^XNΜΆ¬
		}

		return  true;
	}
	//-------------------------------------------------------------------
	//uXVvPt[Ιs€
	void  Object::UpDate()
	{
	}
	//-------------------------------------------------------------------
	//uQc`ζvPt[Ιs€
	void  Object::Render2D_AF()
	{
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