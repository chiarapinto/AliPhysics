AliAnalysisTaskSEHFTenderQnVectors* AddTaskHFTenderQnVectors(TString taskname = "HFTenderQnVectors",
                                                             TString outputSuffix = "", 
                                                             int harmonic = 2, 
                                                             int normmethod = 1,//AliHFQnVectorHandler::kQoverM,
                                                             int calibType = 0,//AliHFQnVectorHandler::kQnCalib, 
                                                             TString AODBfileName = "")
{
    AliAnalysisManager *mgr = AliAnalysisManager::GetAnalysisManager();
    if (!mgr) {
        ::Error("AliAnalysisTaskSEHFTenderQnVectors", "No analysis manager found.");
        return NULL;
    }
    if (!mgr->GetInputEventHandler()) {
        ::Error("AliAnalysisTaskSEHFTenderQnVectors", "This task requires an input event handler");
        return NULL;
    }

    TString type = mgr->GetInputEventHandler()->GetDataType(); // can be "ESD" or "AOD"
    if(type.Contains("ESD")){
        ::Error("AliAnalysisTaskSEHFTenderQnVectors", "This task requires to run on AOD");
        return NULL;
    }

    //========= Add task for standard analysis to the ANALYSIS manager ====
    AliAnalysisTaskSEHFTenderQnVectors *task = new AliAnalysisTaskSEHFTenderQnVectors(taskname.Data(),harmonic,calibType,AODBfileName);
    task->SetNormalisationMethod(normmethod);
    mgr->AddTask(task);

    TString outputfile = AliAnalysisManager::GetCommonFileName();
    outputfile += ":PWGHF_D2H_QnVectorTender";

    //define input container
    AliAnalysisDataContainer *cinput = mgr->CreateContainer(Form("cinputQnVectorTender%s",outputSuffix.Data()),TChain::Class(),AliAnalysisManager::kInputContainer);
    //define output containers
    AliAnalysisDataContainer *coutput = mgr->CreateContainer(Form("coutputQnVectorTender%s",outputSuffix.Data()), TList::Class(),AliAnalysisManager::kOutputContainer,outputfile.Data());

    //connect containers
    mgr->ConnectInput(task,0,mgr->GetCommonInputContainer());
    mgr->ConnectOutput(task, 1, coutput);
    return task;
}
