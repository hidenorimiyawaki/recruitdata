//---------------------------------
//  [ AnimationData ] 
//---------------------------------
//#include "./../../System/stdafx/stdafx.h"
//#include "./../../GeneralPurposeClass/CVector3Class_Def.h"
//#include "./../../DataTreat/StructDefinition.h"

extern const AP c_anime[28] = {
AP(TexturePoint(0.00000f,0.00000f,0.12500f,0.25000f),2,0),	// 立ち				0
AP(TexturePoint(0.12500f,0.00000f,0.25000f,0.25000f),4,2),	// 走り前 
AP(TexturePoint(0.25000f,0.00000f,0.37500f,0.25000f),2,3),	// 走りループ開始 
AP(TexturePoint(0.37500f,0.00000f,0.50000f,0.25000f),2,4),
AP(TexturePoint(0.50000f,0.00000f,0.62500f,0.25000f),2,2),	// 走りループ終了 
AP(TexturePoint(0.62500f,0.00000f,0.75000f,0.25000f),3,6),	// 蹴り				5
AP(TexturePoint(0.00000f,0.25000f,0.18750f,0.50000f),3,7),
AP(TexturePoint(0.18750f,0.25000f,0.37500f,0.50000f),3,8),
AP(TexturePoint(0.37500f,0.25000f,0.56250f,0.50000f),3,9),
AP(TexturePoint(0.56250f,0.25000f,0.75000f,0.50000f),9,10),
AP(TexturePoint(0.87500f,0.00000f,1.00000f,0.25000f),3,2),	// 蹴り終了			10
AP(TexturePoint(0.37500f,0.53125f,0.50000f,0.75000f),2,11),	// ジャンプ開始 
AP(TexturePoint(0.75000f,0.25000f,0.87500f,0.50000f),15,13),
AP(TexturePoint(0.87500f,0.25000f,1.00000f,0.50000f),15,13),
AP(TexturePoint(0.75000f,0.00000f,0.87500f,0.25000f),2,2),	// ジャンプ上昇開始 
AP(TexturePoint(0.00000f,0.50000f,0.12500f,0.75000f),1,16),	// ジャンプ上昇ループ 15
AP(TexturePoint(0.12500f,0.50000f,0.25000f,0.75000f),1,17),
AP(TexturePoint(0.25000f,0.50000f,0.37500f,0.75000f),1,18),	// ジャンプ上昇ループ 
AP(TexturePoint(0.37500f,0.50000f,0.50000f,0.75000f),1,19),	// ジャンプ下降中 
AP(TexturePoint(0.50000f,0.50000f,0.62500f,0.75000f),1,20),	// ジャンプ着地 
AP(TexturePoint(0.62500f,0.50000f,0.75000f,0.75000f),1,21),	// ジャンプ着地 
AP(TexturePoint(0.75000f,0.50000f,0.87500f,0.75000f),1,19),	// ジャンプ着地 
AP(TexturePoint(0.87500f,0.25000f,1.00000f,0.50000f),15,23),
AP(TexturePoint(0.00000f,0.50000f,0.12500f,0.75000f),1,24),
AP(TexturePoint(0.12500f,0.50000f,0.25000f,0.75000f),2,25),
AP(TexturePoint(0.25000f,0.50000f,0.37500f,0.75000f),1,26),
AP(TexturePoint(0.00000f,0.00000f,0.00000f,0.00000f),0,2),
AP(TexturePoint(0.00000f,0.00000f,0.00000f,0.00000f),0,0),
};

