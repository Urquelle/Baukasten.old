block = source:getForm():getVSpace():getEntity( "block:current" )
field = source:getChild("entity:field")

column = field:getState("state:column"):getValue()

curr_matrix = block:getState( "state:currentMatrix" )
next_matrix_num = ( curr_matrix:getValue() % 4 ) + 1

curr_limits = block:getState( "state:limit" .. next_matrix_num )

limit_right = curr_limits:getValue( 1 )
limit_left = curr_limits:getValue( 3 )

block_min = column - limit_left
block_max = column + limit_right

if block_min >= 0 and block_max <= 13 then
	curr_matrix:setValue( next_matrix_num )
end
