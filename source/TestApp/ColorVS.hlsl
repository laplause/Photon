cbuffer PerFrameBuffer
{
	matrix view;
	matrix projection;
};

cbuffer PerInstanceBuffer
{
	matrix world;
};

struct VertexInput
{
	float4 position : POSITION;
	float4 color : COLOR;
};

struct PixelInput
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
};

PixelInput main(VertexInput input)
{
	PixelInput output = (PixelInput)0;

	output.position = mul(input.position, world);
	output.position = mul(output.position, view);
	output.position = mul(output.position, projection);

	output.color = input.color;

	return output;
}