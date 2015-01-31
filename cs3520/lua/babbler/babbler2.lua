function babble(fullstr, n, outlength)
	local outfile = io.open("out.txt", "w")
	local ngrams = n + 0
	local outlen = outlength + 0
	local splitwords = {}
	local nwords = {}
	local shingles = {}
	local shingle = {}
	local word = ""
	for c in fullstr:gmatch(".") do
		if c == " " then
			word = word .. " "
			table.insert(splitwords, word)
			word = ""
		else
			word = word .. c
		end
	end
	table.insert(splitwords, word)
	count=0
	while count <= ngrams do
		count = count + 1
		table.insert(splitwords, splitwords[count])
	end
	len = table.maxn(splitwords)
	count=1
	ncount=0
	while count < (len-ngrams) do
		shingle = {}
		while ncount < ngrams do
			table.insert(shingle, splitwords[ncount+count])
			ncount = ncount + 1
		end
		table.insert(shingles, shingle)
		count = count + 1
		ncount = 0
	end
	math.randomseed(os.time())
	randnum = math.random(count)
	randrange = randnum % outlen
	shingle = shingles[randrange]
	last = shingle[3]
	outstr = ""
	outstr = outstr .. shingle[1] .. shingle[2] .. shingle[3]
	curlen = 3
	print(outstr)
	
	
	while curlen <= outlen do
	--repeat
		randnum = math.random(count)
		randrange = randnum % outlen
		shingle = shingles[randrange]
		if last == shingle[1] then
			curlen = curlen + 2
			last = shingle[3]
			outstr = outstr .. shingle[2] .. shingle[3]
			print(curlen)
			print(outstr)
		end
	--until curlen >= outlen
	end
	
	
	print("hi")
	print(outstr)
	outfile:close()
end




