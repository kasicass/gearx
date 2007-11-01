
--[[
    $Id: $
    
    utility functions
    CopyRight (c) GearX Team, 2007
    See LICENSE for more information

	TAB SIZE: 4
--]]

local Utility = {}

function Utility.printf(fmt, ...)
    print(fmt:format(...))
end

printf = Utility.printf
