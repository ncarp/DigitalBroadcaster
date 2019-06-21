-- =============================================
-- Author:		Pedro Roque, High Precision
-- Create date: 2007-12-2008
-- Description:	Inserts a new Expression 
-- =============================================
CREATE PROCEDURE [dbo].[LanguageAdd]
	-- Add the parameters for the stored procedure here
	@Name char(100),
	@LanguageID int = 0 OUTPUT
AS
BEGIN
	INSERT INTO Languages ([Name],Activ) VALUES (@Name,1)

	SET @LanguageID = Scope_Identity()
END
