#pragma once

#include "PxPhysicsAPI.h"
#include <array>

using namespace physx;

////////////////
/// Skeleton ///
////////////////

namespace Skeleton
{
	enum Enum : PxU8
	{
		pelvis,

		tail,
		tail1,
		tail2,
		tail3,

		spine,
		spine1,
		head,

		count,
		invalid
	};

	/*
	* 
	*  head  <->  spine1  <->  spine  <->  pelvis  <->  tail  <->  tail1  <->  tail2  <->  tail3
	* 
	*/

	static const std::array<Skeleton::Enum, Skeleton::count> parentBones =
	{
		Skeleton::invalid,		// for pelvis

		Skeleton::pelvis,		// for tail
		Skeleton::tail,			// for tail1
		Skeleton::tail1,		// for tail2
		Skeleton::tail2,		// for tail3

		Skeleton::pelvis,		// for spine
		Skeleton::spine,		// for spine1
		Skeleton::spine1,		// for head
	};

	std::array<const char*, Skeleton::count> names =
	{
		"pelvis",

		"tail",
		"tail1",
		"tail2",
		"tail3",

		"spine",

		"spine1",
		"head"
	};

};


namespace Ragdoll
{

/////////////////////
/// Geometry data ///
/////////////////////

static const std::array<physx::PxVec3, 18> convex_pelvis =
{
	physx::PxVec3{-0.101480991, 0.0640427470, 0.0643786639},
	physx::PxVec3{0.0434599221, 0.0767326578, 0.0126064047},
	physx::PxVec3{-0.0987634733, 0.0980954170, -0.0399663635},
	physx::PxVec3{0.104130991, -0.0475642197, 0.0502609275},
	physx::PxVec3{0.00540770357, -0.0980954170, -0.0240750238},
	physx::PxVec3{0.116595142, -0.0228235349, -0.00683363434},
	physx::PxVec3{0.0906911120, 0.0294879619, 0.0721392855},
	physx::PxVec3{-0.112545691, -0.0471990407, 0.0906342342},
	physx::PxVec3{0.100624815, 0.0522658117, 0.0279618427},
	physx::PxVec3{0.107631855, 0.00839905441, -0.0341147929},
	physx::PxVec3{-0.0417520441, -0.0294423234, -0.0804651156},
	physx::PxVec3{-0.0785442218, -0.0427256450, -0.0251350421},
	physx::PxVec3{-0.0434640273, 0.0163416266, -0.0872546658},
	physx::PxVec3{-0.116595142, 0.0643166229, 0.0560665578},
	physx::PxVec3{-0.103139430, -0.0681053773, 0.0570165925},
	physx::PxVec3{0.00158270146, 0.0814343989, -0.0350339934},
	physx::PxVec3{-0.0174878538, 0.00502117397, -0.0906342342},
	physx::PxVec3{0.0191157237, 0.0362437367, 0.0843664482}
};

static const std::array<physx::PxVec3, 18> convex_tail =
{
	physx::PxVec3{-0.0713547990, -0.0154515253, -0.0664712936},
	physx::PxVec3{-0.0927796662, 0.0523343310, -0.0405802764},
	physx::PxVec3{0.0144632589, 0.0491390675, -0.0766718909},
	physx::PxVec3{0.0537995882, -0.0639286041, 0.00665973499},
	physx::PxVec3{0.0388335697, -0.0542971678, -0.0327043384},
	physx::PxVec3{0.0959518328, 0.0322495475, 0.0496224202},
	physx::PxVec3{0.0168213453, -0.0342580676, 0.0634297729},
	physx::PxVec3{-0.0814095512, -0.0631070361, -0.0158983804},
	physx::PxVec3{-0.0959518328, 0.0630157217, 0.000529543497},
	physx::PxVec3{-0.0670359656, -0.0400096215, 0.0297636911},
	physx::PxVec3{-0.0392062739, 0.0307432674, 0.0688565597},
	physx::PxVec3{-0.00268316409, 0.0409225412, 0.0766718909},
	physx::PxVec3{-0.0263037775, 0.0584054105, 0.0509854779},
	physx::PxVec3{0.0202800985, 0.0639286041, -0.0438143983},
	physx::PxVec3{0.0192562044, -0.0422006622, -0.0563539676},
	physx::PxVec3{-0.0758087263, -0.0576750226, -0.0398976877},
	physx::PxVec3{-0.0693337545, 0.0561686978, 0.0430924892},
	physx::PxVec3{0.0533878654, 0.0146298744, -0.0334319435}
};

static const std::array<physx::PxVec3, 18> convex_tail1 =
{
	physx::PxVec3{-0.121467754, -0.0230288897, 0.0192174241},
	physx::PxVec3{-0.0439927801, -0.0244439542, 0.0528856330},
	physx::PxVec3{-0.121858753, 0.0296476502, 0.0229438450},
	physx::PxVec3{-0.111207746, 0.0323865190, -0.0192967504},
	physx::PxVec3{-0.0465189815, 0.0536124073, 0.0243207719},
	physx::PxVec3{0.0646366999, 0.0568532757, 0.00902501214},
	physx::PxVec3{0.0819188431, 0.00860444363, -0.0529353656},
	physx::PxVec3{-0.112334274, -0.0127126826, -0.0253814310},
	physx::PxVec3{0.121858753, -0.0222528931, -0.00234084297},
	physx::PxVec3{0.0709694922, -0.0568532757, 0.00835968740},
	physx::PxVec3{0.00501577929, 0.0309714098, 0.0522901043},
	physx::PxVec3{0.114682220, 0.0368598886, 0.00433516828},
	physx::PxVec3{0.117925622, 0.00892397203, 0.0188558549},
	physx::PxVec3{-0.0529687442, -0.0471304953, 0.0279354043},
	physx::PxVec3{0.0658851862, -0.0249004196, 0.0372846909},
	physx::PxVec3{-0.0472019091, 0.0316561572, 0.0529353656},
	physx::PxVec3{-0.117199697, -0.0290542450, -0.0102428561},
	physx::PxVec3{0.114588752, -0.0167296119, 0.0193444397}
};

static const std::array<physx::PxVec3, 18> convex_tail2 =
{
	physx::PxVec3{0.100061275, -0.0193772186, -0.00625930494},
	physx::PxVec3{0.103660636, 0.00362894870, -0.00194050965},
	physx::PxVec3{0.0391654857, 0.00349200750, 0.0288768820},
	physx::PxVec3{0.100890800, 0.0205183942, -0.00794523582},
	physx::PxVec3{0.0816465244, 0.00390282972, -0.0286831167},
	physx::PxVec3{-0.0934561267, 0.0147668533, -0.0217264257},
	physx::PxVec3{-0.0931406990, -0.00344635756, -0.0288769230},
	physx::PxVec3{-0.102087654, 0.0221616421, -0.00417915219},
	physx::PxVec3{0.0821416825, -0.00942614116, -0.0249382015},
	physx::PxVec3{-0.0926333368, -0.0168666355, -0.0215110742},
	physx::PxVec3{0.0828002170, 0.0155884875, -0.0225113463},
	physx::PxVec3{0.0496265255, 0.0149494279, 0.0147283487},
	physx::PxVec3{-0.103481226, 0.0114345951, 0.00367835700},
	physx::PxVec3{-0.103660636, -0.000890117837, 0.00494948961},
	physx::PxVec3{0.0390223153, -0.00381153286, 0.0266678091},
	physx::PxVec3{0.0496511720, -0.0129866162, 0.0154402414},
	physx::PxVec3{-0.100477211, -0.0198793449, -0.00333839282},
	physx::PxVec3{-0.100024261, -0.0221616421, -0.00727200741}

};

static const std::array<physx::PxVec3, 18> convex_tail3 =
{
	physx::PxVec3{-0.132072479, 0.0168437529, 0.0245296750},
	physx::PxVec3{0.0106359003, -0.000730362255, -0.0800621808},
	physx::PxVec3{-0.138208747, -0.0250602141, 0.0331551060},
	physx::PxVec3{-0.126970991, 0.0245124511, 0.0511473008},
	physx::PxVec3{0.0522427186, -0.0180305745, 0.0376579128},
	physx::PxVec3{-0.0495762862, -0.0390281975, 0.0445076004},
	physx::PxVec3{0.138208747, -0.00159765279, -0.0513909347},
	physx::PxVec3{-0.0375668965, 0.0180762261, 0.0790061876},
	physx::PxVec3{-0.0593940094, 0.0390281975, 0.0363174267},
	physx::PxVec3{-0.0722373948, -0.00538634649, 0.0800621808},
	physx::PxVec3{-0.115757622, -0.00702964049, 0.0683869645},
	physx::PxVec3{-0.0221042912, -0.0157938655, 0.0796012357},
	physx::PxVec3{0.0141811036, 0.00502117397, 0.0753404200},
	physx::PxVec3{0.0519526787, 0.0165242236, 0.0355935358},
	physx::PxVec3{-0.0672019497, -0.0371110477, 0.0124203973},
	physx::PxVec3{-0.110550255, -0.0300813895, 0.0533704348},
	physx::PxVec3{0.0601151548, -0.00387999881, 0.0429138355},
	physx::PxVec3{-0.0787751228, 0.0349656194, 0.0168521516}
};

typedef std::array<physx::PxVec3, 18> ConvexDataArray;

struct Geometry
{
	const ConvexDataArray* convexPointer;
	physx::PxGeometryHolder geometry;
};
 
static const std::array<Geometry, Skeleton::count> geometry =
{
	Geometry{ &convex_pelvis,	physx::PxConvexMeshGeometry()},		// pelvis
	Geometry{ &convex_tail,		physx::PxConvexMeshGeometry()},		// tail
	Geometry{ &convex_tail1,	physx::PxConvexMeshGeometry()},		// tail1
	Geometry{ &convex_tail2,	physx::PxConvexMeshGeometry()},		// tail2
	Geometry{ &convex_tail3,	physx::PxConvexMeshGeometry()},		// tail3
	Geometry{ nullptr,			physx::PxSphereGeometry(0.104f)},	// spine
	Geometry{ nullptr,			physx::PxSphereGeometry(0.079f)},	// spine1
	Geometry{ nullptr,			physx::PxSphereGeometry(0.071f)}	// head
};


//////////////////
/// Local data ///
//////////////////

static const std::array<PxTransform, Skeleton::count> localMassCenters =
{
	physx::PxTransform{ {-0.052, -0.003, -0.033},	{-0.366, 0.085, -0.057, 0.925}	},	// pelvis
	physx::PxTransform{ {0.046, 0.002, 0.001},		{0.378, -0.194, 0.032, 0.905}	},	// tail
	physx::PxTransform{ {0.104, -0.003, 0.001},		{0.010, 0.029, -0.008, 0.999}	},	// tail1
	physx::PxTransform{ {0.089, -0.002, 0.008},		{0.002, -0.012, 0.003, 1.000}	},	// tail2
	physx::PxTransform{ {0.110, 0.001, -0.031},		{0.005, 0.206, 0.004, 0.978}	},	// tail3
	physx::PxTransform{ {0.006, 0.002, 0.011},		{0.004, 0.773, -0.004, 0.635}	},	// spine
	physx::PxTransform{ {0.016, 0.007, -0.000},		{0.000, 0.383, 0.000, 0.924}	},	// spine1
	physx::PxTransform{ {0.048, 0.005, 0.002},		{-0.009, 0.128, 0.429, 0.894}	}	// head
};

static const std::array<PxTransform, Skeleton::count> shapeLocalPose =
{
	physx::PxTransform{ {-0.052, -0.003, -0.033},	{-0.000, -0.000, -0.000, 1.000}	},	// pelvis
	physx::PxTransform{ {0.046, 0.002, 0.001},		{-0.000, -0.000, -0.000, 1.000}	},	// tail
	physx::PxTransform{ {0.104, -0.003, 0.001},		{-0.000, -0.000, -0.000, 1.000}	},	// tail1
	physx::PxTransform{ {0.089, -0.002, 0.008},		{-0.000, -0.000, -0.000, 1.000}	},	// tail2
	physx::PxTransform{ {0.110, 0.001, -0.031},		{-0.000, -0.000, -0.000, 1.000}	},	// tail3
	physx::PxTransform{ {0.006, 0.002, 0.011},		{0.080, 0.001, -0.997, 0.021}	},	// spine
	physx::PxTransform{ {0.016, 0.007, -0.000},		{-0.147, 0.034, 0.651, 0.744}	},	// spine1
	physx::PxTransform{ {0.048, 0.005, 0.002},		{-0.609, -0.743, 0.128, 0.246}	}	// head
};

static const std::array<PxTransform, Skeleton::count> actorGlobalPoses =
{
	physx::PxTransform{ {-2.71079224e-32, 0.776630342, 0.223986104},	{-0.545645237, -0.545645237, -0.449745804, 0.449745804}		},	// pelvis
	physx::PxTransform{ {-5.91219997e-17, 0.718606889, 0.0446449220},	{0.598440528, -0.598440468, -0.376655012, -0.376655042}		},	// tail
	physx::PxTransform{ {-5.00334950e-16, 0.662677526, -0.0719433576},	{0.670349717, -0.670349777, -0.225013837, -0.225013852}		},	// tail1
	physx::PxTransform{ {-3.03123904e-09, 0.473995060, -0.214696273},	{0.692229092, -0.692229152, -0.144287452, -0.144287467}		},	// tail2
	physx::PxTransform{ {-5.34076294e-09, 0.275312603, -0.301284432},	{-0.702925563, 0.702925563, -0.0767832100, -0.0767831728}	},	// tail3
	physx::PxTransform{ {1.20645929e-08, 0.795951843, 0.323329747},		{-0.481948942, -0.481948882, -0.517421484, 0.517421603}		},	// spine
	physx::PxTransform{ {2.63199098e-08, 0.787171304, 0.446860462},		{-0.319874823, -0.319874763, -0.630618691, 0.630618811}		},	// spine1
	physx::PxTransform{ {3.47988411e-08, 0.725312650, 0.531350672},		{-0.297980398, -0.297980309, -0.641254663, 0.641254723}		}	// head
};

static const std::array<PxTransform, Skeleton::count> jointParentPoses =
{
	physx::PxTransform{ },																// pelvis
	physx::PxTransform{ {-0.187, -0.000, -0.023},	{-0.992, -0.000, -0.127, 0.000}	},	// tail
	physx::PxTransform{ {0.129, 0.000, -0.000},		{0.000, -0.972, -0.000, 0.236}	},	// tail1
	physx::PxTransform{ {0.237, -0.000, -0.000},	{-0.000, -0.993, 0.000, 0.118}	},	// tail2
	physx::PxTransform{ {5.826, -9.287, -3.367},	{0.692, -0.692, -0.144, -0.144}	},	// tail3
	physx::PxTransform{ {0.101, 0.000, -0.000},		{0.000, -0.991, -0.000, 0.131}	},	// spine
	physx::PxTransform{ {0.124, -0.000, -0.000},	{-0.000, -0.961, -0.000, 0.277}	},	// spine1
	physx::PxTransform{ {0.105, -0.000, -0.000},	{-0.000, -0.999, -0.000, 0.034}	}	// head
};

} // namespace Ragdoll