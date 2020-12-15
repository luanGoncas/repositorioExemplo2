arquivo = open("entrada.txt", "r")

entrada = arquivo.read()

for i in entrada:
	L = entrada.readlines()
	i++
	V = entrada.readlines()

if L < 1 or L > 500:
	print("Quantidade de lesmas inválida")
else:
	for i in V:
		if i < 1 or i > 50:
			print("Velocidade inválida")
			break
		else:
			for i in L:
				if V[i] > V[i + 1]:
					lesmaRapida = V[i]
				elif V[i] == V[i + 1]?
					lesmaRapida = V[i]
				else:
					lesmaRapida = V[i + 1]

print(lesmaRapida) 