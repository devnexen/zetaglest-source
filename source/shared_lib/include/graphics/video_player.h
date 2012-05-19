// ==============================================================
//	This file is part of MegaGlest Shared Library (www.glest.org)
//
//	Copyright (C) 2012 Mark Vejvoda (mark_vejvoda@hotmail.com)
//
//	You can redistribute this code and/or modify it under
//	the terms of the GNU General Public License as published
//	by the Free Software Foundation; either version 2 of the
//	License, or (at your option) any later version
// ==============================================================
#ifndef VIDEO_PLAYER_H_
#define VIDEO_PLAYER_H_

#include <string>

class SDL_Surface;
class ctx;

using namespace std;

namespace Shared{ namespace Graphics{

class VideoPlayer {
protected:

	string filename;
	SDL_Surface *surface;
	int x;
	int y;
	int width;
	int height;
	int colorBits;

	bool successLoadingLib;
	string pluginsPath;
	bool verboseEnabled;

	bool stop;
	bool finished;

	ctx *ctxPtr;

	void init();

public:
	VideoPlayer(string filename, SDL_Surface *surface, int x, int y,
			int width, int height, int colorBits,
			string pluginsPath,bool verboseEnabled=false);
	virtual ~VideoPlayer();

	void PlayVideo();
	void StopVideo() { stop = true; }

	bool initPlayer();
	void closePlayer();

	bool playFrame(bool swapBuffers = true);
	bool isPlaying() const;

	static bool hasBackEndVideoPlayer();
};

}}

#endif /* VIDEO_PLAYER_H_ */