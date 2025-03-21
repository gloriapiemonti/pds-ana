#include "../../../Class/_c/class_include.hpp"
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

// --- ANA CONFIG ---------------------------------------------------
struct AnaConfig {
  string runs_folder;
  string input_ana_folder;
  string rms_result_file;
  string output_ana_folder;
  double allowed_bsl_rms;
  bool   print_results;
  int display;
  int plot;
  int print;
  int memorydepth;
  double tick_len;
  int nbins;
  int nmaxpeaks;
  string data_format;
};

AnaConfig load_ana_config(const std::string& filename) {
  std::ifstream file(filename);
  if (!file) {
    throw std::runtime_error("Could not open config file: " + filename);
  }

  json j;
  file >> j;
  AnaConfig config;
  config.runs_folder = j.at("runs_folder").get<std::string>();
  config.input_ana_folder = j.at("input_ana_folder").get<std::string>();
  config.rms_result_file = j.at("rms_result_file").get<std::string>();
  config.output_ana_folder = j.at("output_ana_folder").get<std::string>();
  config.allowed_bsl_rms = j.at("allowed_bsl_rms").get<double>();
  config.print_results = j.at("print_results").get<bool>();
  config.display = j.at("display").get<int>();
  config.print = j.at("print").get<int>();
  config.plot = j.at("plot").get<int>();
  config.memorydepth = j.at("memorydepth").get<int>();
  config.tick_len = j.at("tick_len").get<double>();
  config.nbins = j.at("nbins").get<int>();
  config.nmaxpeaks = j.at("nmaxpeaks").get<int>();
  config.data_format = j.at("data_format").get<std::string>();
  return config;
}


// --- MODULE CONFIG ------------------------------------------------
struct ModuleConfig {
  bool invert;
  int n_wf;
  int prepulse_ticks;
  int int_low;
  int int_up;
  double scan_sat_up;

  int module;
  int day;
  std::vector<int> module_channels;
  std::vector<double> biases;
  //std::vector<int> runs;
};

ModuleConfig load_module_config(const std::string& filename) {
  std::ifstream file(filename);
  if (!file) {
    throw std::runtime_error("Could not open config file: " + filename);
  }
  
  json j;
  file >> j;
  
  ModuleConfig config;
  config.invert = j.at("invert").get<bool>();
  config.n_wf = j.at("n_wf").get<int>();
  config.prepulse_ticks = j.at("prepulse_ticks").get<int>();
  config.int_low = j.at("int_low").get<int>();
  config.int_up = j.at("int_up").get<int>();
  config.scan_sat_up = j.at("scan_sat_up").get<double>();

  config.module = j.at("module").get<int>();
  config.module_channels = j.at("module_channels").get<std::vector<int>>();
  config.biases = j.at("biases").get<std::vector<double>>();
  //config.runs = j.at("runs").get<std::vector<int>>();
  
  return config;
}
/*
// Function to calculate the bias voltage, overvoltage and their errors
void DAC_to_Volt(int module, double bias_dac, double& bias_volt, double& err_bias_volt){

  double err_volt_m1_m2 = 0.03; // to have chi2 ~1
  double err_volt_m3_m4 = 0.07; // to have chi2 ~1
  vector<double> dacs, volts;  
  double err_volt;
  if(module==1 || module==2 || module==11){
    dacs = {1148, 1161, 1174, 1187, 1200};
    volts = {45.06, 45.54, 46.09, 46.55, 47.03};
    err_volt = err_volt_m1_m2;
  } else {
    dacs = {754, 767, 780, 793, 806};
    volts = {30.54, 31.11, 31.64, 32.01, 32.52};
    err_volt = err_volt_m3_m4;
  }
  vector<double> err_volts(volts.size(), err_volt);
  vector<double> err_dacs(dacs.size(), 0.);

  TF1* f1 = new TF1 ( "f1", "[0]+[1]*x"); // y = q + m*x

  f1->SetParameter(0, 0.);
  f1->SetParameter(1, (volts[volts.size()-1]-volts[0])/(dacs[dacs.size()-1]-dacs[0]));

  TGraphErrors* g_Volt_DAC = new TGraphErrors(dacs.size(), &dacs[0], &volts[0],
                                              &err_dacs[0], &err_volts[0]);
  
  TFitResultPtr r1 = g_Volt_DAC->Fit(f1 ,"S");
  double this_bias_dac[1] = {bias_dac};
  double err_this_bias_volt[1];
  r1->GetConfidenceIntervals(1, 1, 1, this_bias_dac, err_this_bias_volt, 0.683, false);

  bias_volt = f1->Eval(this_bias_dac[0]);
  err_bias_volt = err_this_bias_volt[0];
  return;
}
*/
