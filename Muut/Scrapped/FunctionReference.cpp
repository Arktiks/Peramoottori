//vector<bool(*)()> Application::updateFunctions;
//vector<void(*)()> Application::drawFunctions;
vector<bool(*)()> Application::contextFunctions;


void Application::AddContextFunction(bool(*Function)())
{
	// Add check so stuff doesn't break.
	contextFunctions.push_back(Function);
}

void Application::RunContextFunctions()
{
	for (std::size_t i = 0; i < contextFunctions.size(); ++i)
		ASSERT((*contextFunctions[i])());
}

//static std::vector<bool (*)()> updateFunctions; ///< Functions that are added into Update() loop.
		//static std::vector<void (*)()> drawFunctions;	///< Functions that are added into DrawFrame() loop.
		static std::vector<bool(*)()> contextFunctions; ///< Functions that are only called once after context initialize.

			public:
		static void AddContextFunction(bool(*Function)());

		void RunContextFunctions(); // Test function.