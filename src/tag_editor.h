/***************************************************************************
 *   Copyright (C) 2008-2009 by Andrzej Rybczak                            *
 *   electricityispower@gmail.com                                          *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA.              *
 ***************************************************************************/

#include "ncmpcpp.h"

#ifdef HAVE_TAGLIB_H

#ifndef _TAG_EDITOR_H
#define _TAG_EDITOR_H

// taglib headers
#include "fileref.h"
#include "tag.h"

#include "mpdpp.h"
#include "screen.h"
#include "settings.h"

class TinyTagEditor : public Screen< Menu<Buffer> >
{
	public:
		virtual void Init();
		virtual void Resize();
		virtual void SwitchTo();
		
		virtual std::string Title();
		
		virtual void EnterPressed();
		virtual void SpacePressed() { }
		virtual void MouseButtonPressed(MEVENT);
		
		virtual bool allowsSelection() { return false; }
		
		virtual List *GetList() { return 0; }
		
		bool SetEdited(MPD::Song *);
		
	private:
		bool GetTags();
		MPD::Song itsEdited;
};

extern TinyTagEditor *myTinyTagEditor;

class TagEditor : public Screen<Window>
{
	public:
		TagEditor() : itsBrowsedDir("/") { }
		
		virtual void Init();
		virtual void Resize();
		virtual void SwitchTo();
		
		virtual std::string Title();
		
		virtual void Refresh();
		virtual void Update();
		
		virtual void EnterPressed();
		virtual void SpacePressed();
		virtual void MouseButtonPressed(MEVENT);
		
		virtual MPD::Song *CurrentSong();
		
		virtual bool allowsSelection() { return w == Tags; }
		virtual void ReverseSelection() { Tags->ReverseSelection(); }
		virtual void GetSelectedSongs(MPD::SongList &);
		
		virtual void ApplyFilter(const std::string &);
		
		virtual List *GetList();
		
		void NextColumn();
		void PrevColumn();
		
		Menu<string_pair> *LeftColumn;
		Menu<string_pair> *Albums;
		Menu<string_pair> *Dirs;
		Menu<std::string> *TagTypes;
		Menu<MPD::Song> *Tags;
		
		/// NOTICE: this string is always in utf8, no need to convert it
		const std::string &CurrentDir() { return itsBrowsedDir; }
		
		static void ReadTags(mpd_Song *);
		static bool WriteTags(MPD::Song &);
		
	private:
		static std::string CapitalizeFirstLetters(const std::string &);
		static void CapitalizeFirstLetters(MPD::Song &);
		static void LowerAllLetters(MPD::Song &);
		static void GetTagList(TagLib::StringList &, const std::string &);
		
		static void GetPatternList();
		static void SavePatternList();
		static MPD::Song::SetFunction IntoSetFunction(char);
		static std::string GenerateFilename(const MPD::Song &, std::string &);
		static std::string ParseFilename(MPD::Song &, std::string, bool);
		
		static void DealWithFilenames(MPD::SongList &);
		
		static std::string TagToString(const MPD::Song &, void *);
		
		std::string itsBrowsedDir;
		std::string itsHighlightedDir;
		
		static const std::string PatternsFile;
		static std::vector<std::string> Patterns;
		
		static const size_t MiddleColumnWidth;
		static size_t LeftColumnWidth;
		static size_t MiddleColumnStartX;
		static size_t RightColumnWidth;
		static size_t RightColumnStartX;
};

extern TagEditor *myTagEditor;

#endif

#endif

