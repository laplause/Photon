#ifndef COMPONENT_H
#define COMPONENT_H

namespace Core
{
	//Abstract base class that defines a zephyr component.
	class Component
	{
	public:
		static enum ComponentType
		{
			RENDERABLE = 0,
			COMPONENT_TYPE_MAX
		};

		Component(ComponentType type);
		virtual ~Component();

		const ComponentType GetType() const;

	protected:
		ComponentType mType;
	};
}
#endif