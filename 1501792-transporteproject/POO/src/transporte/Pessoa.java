package transporte;

public class Pessoa {


	public static void main(String[] args) {
		Bicicleta b1 = new Bicicleta();
		b1.setCarga(15);
		Bicicleta b2 = new Bicicleta();
		b2.setCarga(20);
		Carro c1 = new Carro();
		c1.setCarga(300); 
		Carro c2 = new Carro();
		c2.setCarga(400);
//		c1.acelerar();
//		b1.acelerar();
//		c2.acelerar();
//		b2.acelerar();
		
		Veiculo[] veiculos = new Veiculo[4];
		veiculos[0] = b1;
		veiculos[1] = c1;
		veiculos[2] = b2;
		veiculos[3] = c2;
		
		for (Veiculo v : veiculos) {
			v.acelerar();
		}
	
		TransporteDeCarga[] tcs = new TransporteDeCarga[4];
		tcs[0] = b1;
		tcs[1] = b2;
		tcs[2] = c1;
		tcs[3] = c2;
		
		int cargaTotal = 0;
		for (TransporteDeCarga tc : tcs) {
			tc.transportaCarga();
			cargaTotal += tc.getCarga();
		}
		System.out.println("a carga total é "+cargaTotal+" kilos");
	}

}
