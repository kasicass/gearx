
--[[
	$Id: $
	
	Mouse Message Management
	CopyRight (c) GearX Team, 2007
	See LISENCE for more information

	TAB SIZE: 4
--]]


-------------------------------------------------------------------------------
-- Mouse Listener
MouseListener = {
	_listener = {}
}

-------------------------------------------------------------------------------
-- regist mouse message handlder
-- \param msg: message to be handed
-- \param func: callback function, the callback function must have the x, y 
--              parameter handler
function MouseListener.Regist (msg, func)
	if (not MouseListener._listener[msg]) then
		MouseListener._listener[msg] = {}
	end

	table.insert(MouseListener._listener[msg], func)
end

-------------------------------------------------------------------------------
-- check for mouse message
-- \param msg: which message to be check
-- \param x: x coordinate
-- \param y: y coordinate
function MouseListener.Check (msg, x, y)
	if (not MouseListener._listener[msg]) then return end
	for i, t in ipairs(MouseListener._listener[msg]) do
		local noerr, msg = pcall(t, x, y)
		if (not noerr) then
			return error("call for " .. msg .. "check failed: " .. msg)
		end

		if (msg) then return msg end
	end

	return false
end

-------------------------------------------------------------------------------
-- remove handler
-- \param msg: which msg handler to be removed
-- \param func: which hanlder to be removed
function MouseListener.Remove (msg, func)
	for i, t in ipairs(MouseListener._listener[msg]) do
		if (t == func) then
			table.remove(MouseListener._listener[msg], i)
		end
	end
end


-------------------------------------------------------------------------------
-- remove all handler
function MouseListener.RemoveAll ()
	for v, t in pairs(MouseListener._listener) do
		MouseListener._listener[v] = nil
	end

--	MouseListener._listener = {}
end
