matrix WVPMatrix;	//�ϲ�����
vector color;		//������ɫ

//��������
struct VS_INPUT	
{
	vector position : POSITIONT;
};

//�������
struct VS_OUTPUT
{
	vector position : POSITIONT;
	vector color : COLOR;
};

//������
VS_OUTPUT VxMain(VS_INPUT input)
{
	VS_OUTPUT output;
	
	output.position = mul(input.position, WVPMatrix);
	output.color = color;
	
	return output;

}

