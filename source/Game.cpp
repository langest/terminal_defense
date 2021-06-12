#include <Game.h>

#include <string>
#include <map>
#include <thread>
#include <chrono>
#include <vector>
#include <queue>

#include <Coordinate.h>
#include <Player.h>

namespace termd {

CGame::CGame(CPlayer& player) : mPlayer(player), mGameBoard(player) {
	////initialize input calls
	//std::function<void()> f = [this]() { GUI::move_cursor_left(); };
	//inputcalls['h'] = f;
	//inputcalls[KEY_LEFT] = f;

	//f = [this]() { GUI::move_cursor_up(); };
	//inputcalls['k'] = f;
	//inputcalls[KEY_UP] = f;

	//f = [this]() { GUI::move_cursor_right(mGameBoard.getSizeCols()); };
	//inputcalls['l'] = f;
	//inputcalls[KEY_RIGHT] = f;

	//f = [this]() { GUI::move_cursor_down(mGameBoard.getSizeRows()); };
	//inputcalls['j'] = f;
	//inputcalls[KEY_DOWN] = f;

	//f = [this]() { show_menu(); };
	//inputcalls['m'] = f;


	////Reading tower build buttons from file
	//Tower_loader tl;
	//std::vector<int> tids = tl.id_list();

	//for (int id : tids) {
	//	inputcalls[id] = [&, id]() { build_tower(id); };
	//}
}

void CGame::intro() {
	std::string intromsg("You are a hacker minding your own business when suddenly viruses are invading your terminal! \n\
Viruses (as you all know) begins on the right side and flies to the left. \n\
You lose 1 terminal control point if you let a virus get to the left making you lose some control. \n\
You lose when you lose control over your terminal (reach 0 terminal control points). \n\
You win by defeating ALL the viruses! \n\
\n\
You defend your terminal by building towers.\n\
Towers costs RAM to build, you gain more RAM by destroying viruses\n\
\n\
q - Start the next wave of viruses \n\
i - Build a BASIC TOWER \n\
y - Build a DOWN TOWER \n\
d - Build a RIGHT TOWER \n\
w - Build a WALL \n\
MOVE CURSOR as you normally would (arrows or vim-like)\n");
	GUI::print_string(intromsg);
	GUI::get_input();
	//clear();
	GUI::move_cursor(CCoordinate(BoardR0, BoardC0));
}

void CGame::outro() {
	//clear();
	GUI::move_cursor(CCoordinate(0,0));
	GUI::get_input();
}

void CGame::runBuildPhase() {
	int ch;
	GUI::draw_board_frame(mGameBoard.getSizeRows(), mGameBoard.getSizeCols());
	GUI::draw_intel_frame(mGameBoard.getSizeRows());
	char intelmsg[IntelCols];
	while((ch = GUI::get_input()) != 27 && ch != 'q') {
		//if (inputcalls.find(ch) != inputcalls.end()) {
		//	inputcalls[ch]();
		//}
		mGameBoard.draw();
		GUI::clear_intel(mGameBoard.getSizeCols());
		sprintf(
			intelmsg,
			"RAM: %d\t Terminal Control Points: %d",
			mPlayer.getRam(),
			mPlayer.getControlPoints()
		);
		GUI::print_intel(mGameBoard.getSizeRows(), intelmsg);
		GUI::refresh();
	}
}

bool CGame::runInvasionPhase() {
	char intelmsg[IntelCols];

	//Frame counter setup
	std::queue<std::chrono::time_point<std::chrono::high_resolution_clock> > timestamps;
	std::chrono::time_point<std::chrono::high_resolution_clock> avglimit;
	std::size_t avgseconds = 1;
	std::chrono::milliseconds avgtime(1000 * avgseconds);
	std::size_t avgfps;

	//Framerate limiter setup
	std::chrono::milliseconds interval(1000/Frames);
	std::chrono::time_point<std::chrono::high_resolution_clock> last_update(
			std::chrono::system_clock::now() - interval );
	std::chrono::time_point<std::chrono::high_resolution_clock> cur_update;

	while (mGameBoard.update()) {
		//Framerate counter
		avglimit = std::chrono::system_clock::now() - avgtime;
		while (!timestamps.empty() && timestamps.front() < avglimit) {
			timestamps.pop();
		}
		timestamps.push(std::chrono::system_clock::now());
		avgfps = timestamps.size() / avgseconds;

		//Framerate limiter
		mGameBoard.draw();
		GUI::clear_intel(mGameBoard.getSizeRows());
		snprintf(
			intelmsg,
			IntelCols,
			"RAM: %d\t Terminal Control Points: %d\t FPS: %zd",
			mPlayer.getRam(),
			mPlayer.getControlPoints(),
			avgfps
		);
		GUI::print_intel(mGameBoard.getSizeRows(), intelmsg);
		GUI::refresh();

		cur_update = std::chrono::system_clock::now();
		auto sleep_dur = 2 * interval - std::chrono::duration_cast<std::chrono::milliseconds>(cur_update - last_update);
		last_update = cur_update;
		std::this_thread::sleep_for(sleep_dur);
	}
	mGameBoard.draw();//Redraw the mGameBoard so all projectiles are removed TODO prettier solution since this just instantly removes all their gfx.
	return mGameBoard.hasNextWave();

}

bool CGame::run() {
	intro();
	runBuildPhase();
	while (runInvasionPhase()) {
		if(!mPlayer.isAlive()) {
			outro();
			return false;
		}
		runBuildPhase();
	}
	outro();
	return true;
}

void CGame::runMenu() {
	GUI::clear_intel(mGameBoard.getSizeRows());
	GUI::print_intel(mGameBoard.getSizeRows(), std::string("1.Quit Game    2.Return to game"));

	char ch;
	while ((ch = GUI::get_input()) != '1' && ch != '2');

	GUI::clear_intel(mGameBoard.getSizeRows());
}

}
