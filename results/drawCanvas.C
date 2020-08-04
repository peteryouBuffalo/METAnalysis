void drawCanvas(char* filename, char* cName)
{
	TFile *file = new TFile(filename);
	TCanvas* c = (TCanvas*)file->Get(cName);
	c->Draw();
}
