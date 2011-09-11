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

currentCity = entity:getState( "state:currentCity" )
pointer = entity:getForm():getVSpace():getDrawable("form:pointer")

if currentCity:getValue() == cityConst then
	currentCity:setValue( cityVienna )
	pointer:setPosition( posVienna )
elseif currentCity:getValue() == cityVienna then
	currentCity:setValue( cityBerlin )
	pointer:setPosition( posBerlin )
elseif currentCity:getValue() == cityBerlin then
	currentCity:setValue( cityParis )
	pointer:setPosition( posParis )
elseif currentCity:getValue() == cityParis then
	currentCity:setValue( cityLondon )
	pointer:setPosition( posLondon )
end
