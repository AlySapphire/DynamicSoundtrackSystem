#pragma once

namespace FMOD {

	class Channel;

}

namespace DSS {

	typedef enum {
		eUNIT_MS,
		eUNIT_SAMPLES
	}eMARKER_FORMAT;

	class Marker {
	public:

		void SetMarkerPos(unsigned int p_Pos, eMARKER_FORMAT p_Unit);
		const unsigned int & GetMarkerPos();

	protected:

		unsigned int m_Position;
		eMARKER_FORMAT m_Unit;

	};

}