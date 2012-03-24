block = source:form():lSpace():entity( "block:current" ):form()
field = source:child("entity:field")

curr_matrix = block:state( "state:currentMatrix" )
next_matrix_num = ( curr_matrix:value() % 4 ) + 1
matrix = block:state( "state:matrix" )

curr_matrix:setValue( next_matrix_num )
matrix:setValues(block:state( "state:matrix" .. next_matrix_num ))
field:form():state("block:current"):setValues(matrix)
