if entity == nil then
	return
end

if not entity:hasState("hp") then
	return
end

state = entity:getState("hp")
source = action:getSource()

if not (source == entity) then
	source:invokeAction("addExperience")
	source:runActions()
end

state:setValue( state:getValue() - 10 )
state = entity:getState("hp")

name = source:getState("name")
targetName = entity:getState("name")

print(name:getValue() .. " just hit " .. targetName:getValue() .. "." )

if state:getValue() <= 0 then
	state:setValue(0)
	entity:invokeAction("die")
end
