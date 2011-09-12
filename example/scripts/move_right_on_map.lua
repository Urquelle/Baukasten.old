posLondon	= t_pos( 255, 330, 0 )
posParis	= t_pos( 295, 420, 0 )
posBerlin	= t_pos( 485, 355, 0 )
posVienna	= t_pos( 565, 480, 0 )
posConst	= t_pos( 845, 670, 0 )

cityConst	= "konstantinopel"
cityVienna	= "vienna"
cityBerlin	= "berlin"
cityParis	= "paris"
cityLondon	= "london"

pointer = entity:getChild( "entity:pointer" )
currentCity = pointer:getState( "state:currentCity" )
form = pointer:getForm()

if currentCity:getValue() == cityLondon then
	currentCity:setValue( cityParis )
	form:setPosition( posParis )
elseif currentCity:getValue() == cityParis then
	currentCity:setValue( cityBerlin )
	form:setPosition( posBerlin )
elseif currentCity:getValue() == cityBerlin then
	currentCity:setValue( cityVienna )
	form:setPosition( posVienna )
elseif currentCity:getValue() == cityVienna then
	currentCity:setValue( cityConst )
	form:setPosition( posConst )
end
