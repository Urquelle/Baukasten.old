posLondon	= t_pos( 250, 310, 0 )
posParis	= t_pos( 275, 405, 0 )
posBerlin	= t_pos( 467, 338, 0 )
posVienna	= t_pos( 560, 470, 0 )
posConst	= t_pos( 840, 655, 0 )

cityConst	= "city:constantinopel"
cityVienna	= "city:vienna"
cityBerlin	= "city:berlin"
cityParis	= "city:paris"
cityLondon	= "city:london"

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
