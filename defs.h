#pragma once
enum status {
	continuing,
	intersection,
	end1,
	black,
	exit1,
	count
};
enum ActionType {
	build,
	sim,
	reenter,
	save,
	load,

	mod_count
};
enum MODE {
	DESIGN,
	SIMULATION,

	M_count
};
enum drawmode {
	building,
	initializing,

	derw_count

};
enum buildmode {
	keyboard,
	mouse,

	bumod_count
};