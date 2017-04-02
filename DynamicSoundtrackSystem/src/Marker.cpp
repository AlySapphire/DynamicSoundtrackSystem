#include "Marker.hpp"

#include <fmod.hpp>
#include <fmod_errors.h>

namespace DSS {

	

	void Marker::SetMarkerPos(unsigned int p_Pos, eMARKER_FORMAT p_Unit) {

		//Set the unit and format
		m_Unit = p_Unit;
		m_Position = p_Pos;

	}

	const unsigned int & Marker::GetMarkerPos() {
		return m_Position;
	}

}