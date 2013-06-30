#include <math.h>

//计算节圆半径
	float rp = A / 2;
	//计算节圆半径
	float i = 2 * Z / M_PI * (D / A - 1);
	//计算压力角
	float ap = atan( sqrt( (1 - i*i)/i ) );
	//计算基圆半径
	float r0 = A * i / 2;
	//起始圆半径??????g?
	float r1 = r0 * g * sqrt( 1 + (tan(ap) - M_PI / (2 * Z))**2 );
	//终点圆半径
	float rn = r0 * g * sqrt( 1 + (tan(ap) + M_PI / (2 * Z))**2 );
	//始点压力角
	float a1 = atan( sqrt( 1 - (r0 / r1)**2 ) / (r0 / r1) );
	//终点压力角
	float an = atan( sqrt( 1 - (r0 / r1)**2 ) / (r0 / r1) );
	//以叶轮中心 O 为原点,过渐开线终点 B 引射线与长轴成夹角 γj?????????
	float ij = M_PI / Z + ( tan(ap) - ap ) - ( tan(an) - an);
	//非工作面宽度
	float S = 2 * rn * sin(ij);
	//非工作面圆弧半径
	float rs = M_PI / Z * g * r;
	//叶轮最大宽度
	float b0 = 2 * r0 * ( tan(ap) - ap + M_PI / (2 * Z) );
	//叶轮实际宽度
	float b = b0 - delta1 / 1000;
	//叶轮最小宽度
	float bb = A - 2 * rs;
	//设:
	float cs = 2 * Z * ( D - A ) / ( M_PI * A );
	float si = sqrt ( 1 - cs * cs );
	//面积利用系数:
	float ln = 1 - 4 * M_PI * ( M_PI / Z + ( si / cs + M_PI / (2*Z))^3 / 3 - ( si / cs - M_PI / (2*Z) )^3 / 3) / ( M_PI * ( 2 / cs + M_PI / Z ) );

