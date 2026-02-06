#pragma once
#ifndef __CLIENT_ENUM_H__
#define __CLIENT_ENUM_H__

#pragma region ENEMY
enum class E_ENEMY_TYPE {
	E_ENEMY_NONE = -1,
	E_ENEMY_VILLAGER = 0,
	E_ENEMY_ZOMBIE = 1,
	E_ENEMY_MAX
};



#pragma region ITEMS

//ITEM:(힐템, 음식, 마나템, 이상효과 제거 아이템, 투척무기, 일회용 사용무기, 탄약, 열쇠)
enum class E_ITEM_TYPE {
	E_ITEM_NONE = -1,
	E_ITEM_BANDAGES = 0,//heal + 10
	E_ITEM_FIRSTAIDKIT = 1,//fully heals hp.
	E_ITEM_ALCOHOL = 2,//replenishes mind.
	E_ITEM_ELIXIR = 3,//fully replenishes mind
	E_ITEM_CHOCKYBAR = 4,//hp+5, mp+5
	E_ITEM_PIZZA = 5,//hp+10, mp+10
	E_ITEM_CHICKEN = 6,//hp+15, mp+15
	E_ITEM_DISPOSABLEKEY = 7,//a disposable key to unlock doors
	E_ITEM_AMMO = 8,//ammunition for firearms
	E_ITEM_MAX
};

//MELEE: (근접무기 ONLY)
enum class E_MELEE_TYPE {
	E_MELEE_NONE = -1,
	E_MELEE_DAGGER = 0,
	E_MELEE_LONGSWORD = 1,
	E_MELEE_BASEBALLBAT = 2,
	E_MELEE_WHIP = 3,
	E_MELEE_CHAINSAW = 4,
	E_MELEE_MAX
};

//GEAR: 각 장비마다 능력치 부여, 별도의 클래스 필요 X, 각종 능력치 부여하는 악세사리, 총기류
enum class E_GEAR_TYPE {
	E_GEAR_NONE = -1,
	//TORSO
	E_GEAR_POLOSHIRT = 0,
	E_GEAR_DENIMSHIRT = 1,
	E_GEAR_BULLETPROOFVEST = 2,
	//HEAD
	E_GEAR_GLASSES = 3,
	E_GEAR_LASERSIGHT = 4,
	E_GEAR_HELMET = 5,
	//FEET
	E_GEAR_RUNNINGSHOES = 6,
	E_GEAR_WHEELIES = 7,
	E_GEAR_BASKETBALLSHOES = 8,

	E_GEAR_MAX
};

#pragma endregion ITEMS

#pragma region MENUOBJ

enum class E_MENUOBJ_TYPE {
	E_MENUOBJ_NONE = -1,
	E_MENUOBJ_STARTGAME = 0,
	E_MENUOBJ_RESUMEGAME = 1,
	E_MENUOBJ_QUITGAME = 2,
	E_MENUOBJ_MAX
};

#pragma endregion MENUOBJ

#pragma region LEVELTYPE

enum class E_LEVEL_TYPE {
	E_LEVELTYPE_NONE = -1,
	E_LEVELTYPE_MENU = 0,
	//E_LEVELTYPE_SELCHAR = 2,
	E_LEVELTYPE_FIELD = 1,
	E_LEVELTYPE_BATTLE = 2,
	E_LEVELTYPE_SKILLTREE = 3,
	E_LEVELTYPE_STAT = 4,

	E_LEVELTYPE_MAX
};

#pragma endregion LEVELTYPE

#endif//!__CLIENT_ENUM_H__