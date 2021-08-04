#pragma once

#include <cstdint>
#include <type_traits>

using ComponentId = std::uint8_t;

struct ComponentIdCounter {
	static int counter;
};


template <typename ComponentType>
struct Component {
	static inline int family() {
		static int family = ComponentIdCounter::counter++;
		return family;
	}
};

template <typename ComponentType>
static int getComponentFamily() {
	return Component<typename std::remove_const<ComponentType>::type>::family();
}


