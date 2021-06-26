package transporte;

public class Carro implements Veiculo, TransporteDeCarga{

	private int carga;
	
	
	public int getCarga() {
		return carga;
	}

	public void setCarga(int carga) {
		this.carga = carga;
	}

	void pisarNoAcelerador() {
		System.out.println("pisando no acelerador");
	}
	
	void apertarBotao() {
		System.out.println("apertando botao...");
	}
	void pisarNoFreio() {
		System.out.println("pisando no freio...");
	}

	@Override
	public void acelerar() {
		apertarBotao();
		
	}

	@Override
	public void parar() {
		pisarNoFreio();
		
	}
	@Override
	public void transportaCarga() {
		System.out.println("carro transportando "+carga+" kilos");
		
	}
}
