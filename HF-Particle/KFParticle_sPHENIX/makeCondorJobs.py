import os

def makeCondorJob(quarkFilter = "Charm"):
    inputFileList = "fileList_MDC_" + quarkFilter + ".txt"
    infile = open(inputFileList, "r")
    line = infile.readline()
    while line:
        line = infile.readline()
        splitLine = line.split("/")
        fileName = splitLine[-1]
        fileName = fileName.replace('\n', '')
        productionNumber = line[-11: -6]

        myOutputPath = os.getcwd()
        os.makedirs("{}/condorJobs/log".format(myOutputPath), exist_ok=True)
        condorOutputInfo = "{0}/condorJobs/log/condor-{1}-{2}".format(myOutputPath, quarkFilter, productionNumber)

        condorFileName = open("condorJobs/condorJob_" + quarkFilter + "_" + productionNumber + ".job", "w")
        condorFileName.write("Universe        = vanilla\n")
        condorFileName.write("Executable      = {}/run_KFParticle.sh\n".format(myOutputPath))
        condorFileName.write("Arguments       = \"/sphenix/user/cdean/MDC1/pythia8/HeavyFlavorTG/data {}\"\n".format(fileName))
        condorFileName.write("Output          = {0}.out\n".format(condorOutputInfo))
        condorFileName.write("Error           = {0}.err\n".format(condorOutputInfo))
        condorFileName.write("Log             = {0}.log\n".format(condorOutputInfo))
        condorFileName.write("Initialdir      = {}\n".format(myOutputPath))
        condorFileName.write("PeriodicHold    = (NumJobStarts>=1 && JobStatus == 1)\n")
        condorFileName.write("request_memory = 4GB\n")
        condorFileName.write("Priority        = 20\n")
        condorFileName.write("job_lease_duration = 3600\n")
        condorFileName.write("Queue 1\n")
        
makeCondorJob()
