#pragma once

namespace logs
{
	void				add(const char* format, ...);
	void				addv(const char* format, const char* param);
	void				add(int id, const char* format, ...);
	void				addv(int id, const char* format, const char* param);
	void				clear(bool clear_text = false);
	int					getcount();
	extern const char*	getpanel(int index);
	char*				getptr();
	int					input(bool interactive = true, bool clear_text = true, const char* format = 0, ...);
	int					inputv(bool interactive, bool clear_text, const char* format, const char* param, const char* element);
	bool				loadart(const char* url);
	void				next(bool interactive = true);
	void				open(const char* title, bool resize = false);
	void				sort();
	bool				yesno(bool interactive = true, const char* format = 0, ...);
}
