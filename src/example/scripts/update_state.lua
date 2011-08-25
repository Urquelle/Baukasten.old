source = action:getSource()

-- get the needed states
name = entity:getState( "name" )
hp = entity:getState( "hp" )
keepRunning = source:getState( "keepRunning" )

-- check whether the target is gomez
if name:getValue() == "gomez" then
	if hp:getValue() == 0 then
		print( "gomez, our great leader ... is ... dead!!" )
		print( "... GAME OVER! ..." )
		keepRunning:setValue( false )
	end
end
