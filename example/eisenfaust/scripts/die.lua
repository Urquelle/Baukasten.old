source = action:getSource()
name = entity:getState( "name" )
print( name:getValue() .. ": it's ... over ... at last ... Hnnnng" )

if name:getValue() == "gomez" then
	print( "gomez ... our ... great leader ... is DEAD!!1!" )
end
