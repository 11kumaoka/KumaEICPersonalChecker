import ROOT

f_in = ROOT.TFile.Open("../../../inputFiles/pythia500kHz_timeframe_newGeo.root")
f_out = ROOT.TFile("./oFIle.root", "RECREATE")

# you can extrackt any entry numbers you want
target_entries = {803}

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