#pragma once
#include <memory>
#include <assert.h>

class ZBuffer
{
public:
	ZBuffer(int width, int height)
		: 
		width(width), 
		height(height),
		zbuffer(std::make_unique<float[]>(width * height))
	{}
	ZBuffer(const ZBuffer&) = delete;
	ZBuffer& operator=(const ZBuffer&) = delete;
	void Clear()
	{
		const int nDepths = width * height;
		for (int i = 0; i < nDepths; i++)
		{
			zbuffer[i] = std::numeric_limits<float>::infinity();
		}
	}
	float& At(int x, int y)
	{
		assert(x >= 0);
		assert(x < width);
		assert(y >= 0);
		assert(y < height);
		return zbuffer[y * width + x];
	}
	const float& At(int x, int y) const
	{
		return const_cast<ZBuffer*>(this)->At(x, y);
	}
	bool TestAndSet(int x, int y, float depth)
	{
		float& depthInBuffer = At(x, y);
		if (depth < depthInBuffer)
		{
			depthInBuffer = depth;
			return true;
		}
		return false;
	}
private:
	std::unique_ptr<float[]> zbuffer;
	int width;
	int height;
};