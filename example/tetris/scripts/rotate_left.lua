block = source:getForm():getVSpace():getEntity( "block:current" )
state = block:getState( "state:currentMatrix" )
state:setValue( ( state:getValue()  % 4 ) + 1 )
