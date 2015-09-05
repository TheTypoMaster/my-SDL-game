
distance = 10
--x axis--
if followX < followerX + distance then
	followerX = followerX - speed
end

if followX + followW > followerX then
	followerX = followerX + speed
end
--y axis--
if followY < followerY + distance then
	followerY = followerY - speed
end

if followY + followH > followerY then
	followerY = followerY + speed
end

return followerX, followerY