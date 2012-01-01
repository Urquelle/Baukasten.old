block = source:getForm():getLSpace():getEntity( "block:current" ):getForm()
field = source:getChild("entity:field")

curr_matrix = block:getState( "state:currentMatrix" )
next_matrix_num = ( curr_matrix:getValue() % 4 ) + 1
matrix = block:getState( "state:matrix" )

curr_matrix:setValue( next_matrix_num )
matrix:setValues(block:getState( "state:matrix" .. next_matrix_num ))
field:getForm():getState("block:current"):setValues(matrix)
