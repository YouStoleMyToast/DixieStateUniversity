function babble(fullstr, n, outlength)
	local outfile = io.open("out.txt", "w")
	local ngrams = n + 0
	local outlen = outlength + 0
	local splitwords = {}
	local final = {}
	local keys = {}
	local words = {}
	for c in fullstr:gmatch("%S+") do
		table.insert(splitwords, c)
	end
	count=0
	while count < ngrams do
		count = count + 1
		table.insert(splitwords, splitwords[count])
	end
	wordcount=table.maxn(splitwords)
	for keya,stra in pairs(splitwords) do
		if keya < (wordcount-ngrams+1) then
			keystr = splitwords[keya] .. " " .. splitwords[keya+1]
			value = splitwords[keya+2]
			table.insert(words,value)
			final[keystr] = words
		end
		words={}
	end
	line1=0
	line2=0
	for keyb, strb in pairs(final) do
		line1=line1+1
		line2=0
		for keyc, strc in pairs(final) do
			line2=line2+1
			if keyb == keyc and line1 ~= line2 then
				table.remove(final,keyb)
			end
		end
	end
	--only unique keys are left now to get list of words that follow them
	wordcount=table.maxn(splitwords)
	for keya,stra in pairs(splitwords) do
		if keya < (wordcount-ngrams+1) then
			keystr = splitwords[keya] .. " " .. splitwords[keya+1]
			value = splitwords[keya+2]
			for keyd,strd in pairs(final) do
				if keystr == keyd then
					table.insert(strd,value)
					
				end
			end
		end
	end	
	for keye,stre in pairs(final) do
		for keyf,strf in pairs(stre) do
		end 
	end
	wordcount=table.maxn(splitwords)
	math.randomseed(os.time())
	maxlen = table.maxn(splitwords)
	randnum = math.random(maxlen-1)
	baseword = "error: not assigned"
	basekey = "error: not assigned"
	nextword = "error: not assigned"
	for keya,stra in pairs(splitwords) do
		if keya == randnum then
			basekey = splitwords[keya] .. " " .. splitwords[keya+1]
			baseword = splitwords[keya+1]
		end
	end
	outtable = {}
	table.insert(outtable,baseword)
	for wordcount = 0, outlen, 1 do
		for keyg,strg in pairs(final) do
			if keyg == basekey then
				maxlen = table.maxn(strg)
				randnum = math.random(maxlen)
				for keyh,strh in pairs(strg) do
					if keyh == randnum then
						nextword = strh
						table.insert(outtable,nextword)
						baseword = nextword
						wordcount = wordcount + 1
					end
				end
			end
		end
		basekey = outtable[table.maxn(outtable)-1] .. " " .. outtable[table.maxn(outtable)]
	end
	outstring = ""
	for i,j in pairs(outtable) do
		outstring = outstring .. " " .. j
	end
	print(outstring)
	outfile:close()
end
