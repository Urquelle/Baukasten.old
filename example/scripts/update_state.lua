source = action:getSource()
gomez = source:getChild( "gomez" )
keepRunning = source:getState( "keepRunning" )

if gomez == nil then
	return
end

hp = gomez:getState( "hp" )

if hp:getValue() == 0 then
	print( "gomez, our great leader ... is ... dead!!" )
	print( "... GAME OVER! ..." )
	keepRunning:setValue( false )
end
