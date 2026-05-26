import ROOT

f_in = ROOT.TFile.Open("/home/tkumaoka/eic/inputFiles/bkgMix/BE10x100/Q2eq1/pythia8NCDIS_10x100_minQ2=1_WBKG.edm4hep.root")
f_out = ROOT.TFile("/home/tkumaoka/eic/inputFiles/testOneEvents/pythia8NCDIS_10x100_minQ2eq1_WBKG.edm2hep.root", "RECREATE")

# you can extrackt any entry numbers you want
target_entries = {0, 1, 2, 3, 4}

for key in f_in.GetListOfKeys():
    obj = key.ReadObj()
    if not obj.InheritsFrom("TTree"):
        continue

    tree_name = obj.GetName()
    tree_in = obj

    # you can change "events" to any tree name you want to extract entries from
    if tree_name == "events":
        tree_out = tree_in.CloneTree(0)
        
        for i in target_entries:
            if i >= tree_in.GetEntries():
                print(f"Warning: Entry {i} out of range for TTree '{tree_name}'")
                continue
            tree_in.GetEntry(i)
            tree_out.Fill()

        f_out.cd()
        tree_out.Write()

    else:
        f_out.cd()
        tree_copy = tree_in.CloneTree(-1)
        tree_copy.Write()

f_out.Close()
f_in.Close()