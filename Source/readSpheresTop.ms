MacroScript ArthoPacini
category:"ArthoPacini" 
tooltip:"Cluster"
buttonText:"Art Cluster"
(
	try(closeRolloutFloater FloaterCluster) catch ()
	try(closeRolloutFloater JanelaPrincipal) catch ()

	rollout JanelaPrincipal "Clusterizacao"
	(
		button localDosDados "Procurar arquivo"
		button rodarScript "Ler arquivo"
		local arqPath
		
		on localDosDados pressed do
		(
			arqPath = getOpenFilename caption: "Open File" types: "txt (*.txt)|*.jpg|Exr (*.exr)|*.exr|Tif (*.tif)|*.tif|ALL|*.*|"
		)
		
		on rodarScript pressed do
		(
			arquivo = openFile arqPath mode:"r"
			while not EOF arquivo do
			(
				linha = readLine arquivo
				novaEsfera = sphere()
				novaEsfera.name = linha
				
				linha = readLine arquivo
				coordX = 3.1415
				coordX = linha as float
				
				linha = readLine arquivo
				coordY = 3.1415
				coordY = linha as float
				
				linha = readLine arquivo	
				coordZ = 3.1415
				coordZ = linha as float
				
				linha = readLine arquivo
				raio = 3.1415
				raio = linha as float
				
				novaEsfera.pos = [coordX, coordY, coordZ]
				novaEsfera.radius = raio
				
			)

			close arquivo
			free arquivo
		)
	)

	FloaterCluster = newrolloutfloater "Clusterizacao" 200 150
	addrollout JanelaPrincipal FloaterCluster 
)

print "Finalizado"