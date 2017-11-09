import ROOT as r

if __name__ == '__main__':
    from argparse import ArgumentParser
    parser = ArgumentParser(description='Display the spectra for cosmic ray primaries at a given altitude')
    parser.add_argument('rootfile', help='ROOT file with histograms')
    args = parser.parse_args()

    # configure the canvas

    c = r.TCanvas()

    f = r.TFile(args.rootfile)
    f.cd('primaries')
    hists = [k.ReadObj() for k in r.gDirectory.GetListOfKeys()]
    hists.sort(key=lambda h: h.GetMaximum(), reverse=True)
    
    for i,h in enumerate(hists):
        h.SetStats(False)
        h.SetLineColor(i+1)
        h.GetXaxis().SetTitle('Kinetic Energy (MeV)')
        h.Draw('same')

    
    r.gPad.SetLogx()
    r.gPad.SetLogy()
    r.gPad.BuildLegend()

    hists[0].SetTitle('Primary Energy Spectrum (%s)' % args.rootfile[:-5])


    raw_input('Press any key to continue')

