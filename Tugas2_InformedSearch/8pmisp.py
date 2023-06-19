def move(ar,pos,st):
	# value maksimal heuristic 
	rh=999999 
	#copy penyimpanan state
	store_st= st.copy()	

	for i in range(len(ar)):
		#penggandaan state
		dupl_st= st.copy() 
		#temp berisi 0 (atau elemen yg menempati 
		# bekas posisi 0 pada iterasi sebelumnya)
		temp = dupl_st[pos]
		#array dg indeks pos (tadinya isi 0)sekarang berisi tetangga 0
		dupl_st[pos] = dupl_st[arr[i]] 
		#nilai temp dikembalikan ke dalam array
		dupl_st[arr[i]] = temp 
		#hitung misposition tiles dalam state
		temp_rh = count(dupl_st) 
		#jika misposition lebih sedikit dari iterasi sebelumnya
		#state diganti
		if temp_rh < rh: 	
			#nilai misposition diganti
			rh = temp_rh 
			#state diganti
			store_st = dupl_st.copy() 
	return store_st,rh 

def print_in_format(matrix):
	for i in range(9):
		if i%3 == 0 and i > 0:
			print("")
		print(str(matrix[i])+" ",end = "")

def count(s):
	c=0
	ideal = [1,2,3,
			4,5,6,
			7,8,0]
	for i in range(9):
		if s[i] != 0 and s[i]!=ideal[i]: 
			c+=1						 
	return c	

state = [ 1,2,3,0,4,6,7,5,8]
h = count(state)
Level = 1

print("\nstep "+str(Level))
print_in_format(state)
print("\nmisplaced tiles : "+str(h))

while h > 0:
	pos = int(state.index(0))
	Level+=1
	#kemungkinan bergerak elemen isi 0 tergantung posisi saat ini
	if pos == 0:		
		arr=[1,3]
		state, h = move (arr,pos,state)
	elif pos == 1:
		arr=[0,2,4]
		state, h = move (arr,pos,state)
	elif pos == 2:
		arr=[1,5]
		state, h = move (arr,pos,state)
	elif pos == 3:
		arr=[0,4,6]
		state, h = move (arr,pos,state)
	elif pos == 4:
		arr=[1,3,5,7]
		state, h = move (arr,pos,state)
	elif pos == 5:
		arr=[2,4,8]
		state, h = move (arr,pos,state)
	elif pos == 6:
		arr=[3,7]
		state, h = move (arr,pos,state)
	elif pos == 7:
		arr=[4,6,8]
		state, h = move (arr,pos,state)
	elif pos == 8:
		arr=[5,7]
		state, h = move (arr,pos,state)
	
	print("\nstep "+str(Level))
	print_in_format(state)
	print("\nMisplaced tiles : "+str(h))





	# helmi a, reff https://github.com/faisal-ansarii/8-puzzle-problem-heuristic-misplaced-tiles-ai-python/blob/main/8-puzzle-problem-ai-python.py