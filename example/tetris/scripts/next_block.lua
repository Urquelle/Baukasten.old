initial_position = t_pos( 400, 20, 0 )

block_list = { "block:i", "block:j", "block:z", "block:s", "block:l", "block:t", "block:o" }
math.randomseed( os.time() )

-- get random block from block_list array
next_block = block_list[ math.random(1, 7) ]

-- get the appropriate game entity to the next_block
block = source:getChild( next_block )

-- add block and its form to L/VSpace
source:getParent():getForm():addToLSpace( block )
source:getParent():getForm():addToVSpace( "block:current", block:getForm() )
block:getForm():setPosition( initial_position )
