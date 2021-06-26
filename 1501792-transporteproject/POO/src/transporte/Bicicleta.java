package transporte;


public class Bicicleta implements Veiculo, TransporteDeCarga{

	private int carga;
	
	public int getCarga() {
		return carga;
	}

	public void setCarga(int carga) {
		this.carga = carga;
	}

	void pedala() {
		System.out.println("pedalando");
	}
	
	void travaPedal() {
		System.out.println("travando pedal");
	}

	@Override
	public void acelerar() {
		pedala();	
	}

	@Override
	public void parar() {
		
		travaPedal();
	}

	@Override
	public void transportaCarga() {
		System.out.println("bicicleta transportando "+carga+" kilos");
		
	}
}
