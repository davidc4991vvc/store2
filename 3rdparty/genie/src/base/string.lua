--
-- string.lua
-- Additions to Lua's built-in string functions.
-- Copyright (c) 2002-2008 Jason Perkins and the Premake project
--


--
-- Returns an array of strings, each of which is a substring of s
-- formed by splitting on boundaries formed by `pattern`.
<<<<<<< HEAD
-- 
=======
--
>>>>>>> upstream/master

	function string.explode(s, pattern, plain)
		if (pattern == '') then return false end
		local pos = 0
		local arr = { }
		for st,sp in function() return s:find(pattern, pos, plain) end do
			table.insert(arr, s:sub(pos, st-1))
			pos = sp + 1
		end
		table.insert(arr, s:sub(pos))
		return arr
	end
<<<<<<< HEAD
	
=======

>>>>>>> upstream/master


--
-- Find the last instance of a pattern in a string.
--

	function string.findlast(s, pattern, plain)
		local curr = 0
<<<<<<< HEAD
		repeat
			local next = s:find(pattern, curr + 1, plain)
			if (next) then curr = next end
		until (not next)
		if (curr > 0) then
			return curr
		end	
=======
		local term = nil
		repeat
			local next, nextterm = s:find(pattern, curr + 1, plain)
			if (next) then
				curr = next
				term = nextterm
			end
		until (not next)
		if (curr > 0) then
			return curr, term
		end
>>>>>>> upstream/master
	end



--
-- Returns true if `haystack` starts with the sequence `needle`.
--

	function string.startswith(haystack, needle)
		return (haystack:find(needle, 1, true) == 1)
	end
<<<<<<< HEAD
=======

	--
	-- remove leading and trailing whitespace from string.
	--

	function string.trim(s)
		return (s:gsub("^%s*(.-)%s*$", "%1"))
	end
>>>>>>> upstream/master
