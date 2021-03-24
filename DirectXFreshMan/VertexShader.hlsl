matrix WVPMatrix;	//合并矩阵
vector color;		//顶点颜色

//管线输入
struct VS_INPUT	
{
	vector position : POSITIONT;
};

//管线输出
struct VS_OUTPUT
{
	vector position : POSITIONT;
	vector color : COLOR;
};

//主函数
VS_OUTPUT VxMain(VS_INPUT input)
{
	VS_OUTPUT output;
	
	output.position = mul(input.position, WVPMatrix);
	output.color = color;
	
	return output;

}

