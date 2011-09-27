block = source:getForm():getVSpace():getEntity( "block:current" )
current_position = block:getPosition()
next_position = t_pos( current_position:getX() + 40, current_position:getY(), current_position:getZ() )
block:setPosition( next_position )
